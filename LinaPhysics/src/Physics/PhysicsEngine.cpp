/*
Author: Inan Evin
www.inanevin.com

Copyright 2018 Inan Evin

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions
and limitations under the License.

Class: PhysicsEngine
Timestamp: 5/1/2019 2:35:43 AM

*/

#include "Physics/PhysicsEngine.hpp"  
#include "Utility/Log.hpp"
#include "ECS/Components/RigidbodyComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "Utility/UtilityFunctions.hpp"

namespace LinaEngine::Physics
{
	PhysicsEngine::PhysicsEngine()
	{
		LINA_CORE_TRACE("[Constructor] -> Physics Engine ({0})", typeid(*this).name());

		
	}

	PhysicsEngine::~PhysicsEngine()
	{
		LINA_CORE_TRACE("[Destructor] -> Physics Engine ({0})", typeid(*this).name());

		for (std::map<int, btRigidBody*>::iterator it = m_bodies.begin(); it != m_bodies.end(); ++it)
		{
			if (it->second->getMotionState())
			{
				delete it->second->getCollisionShape();
			}
		}

		//remove the rigidbodies from the dynamics world and delete them
		for (int i = m_world->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = m_world->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			m_world->removeCollisionObject(obj);
			delete obj;
		}

		delete m_world;
		delete m_impulseSolver;
		delete m_overlappingPairCache;
		delete m_collisionDispatcher;
		delete m_collisionConfig;
	}

	void PhysicsEngine::Initialize(LinaEngine::ECS::ECSRegistry& ecsReg)
	{
		LINA_CORE_TRACE("[Initialization] -> Physics Engine ({0})", typeid(*this).name());

		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		m_collisionConfig = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfig);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		m_overlappingPairCache = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		m_impulseSolver = new btSequentialImpulseConstraintSolver;

		// Create dynamics world
		m_world = new btDiscreteDynamicsWorld(m_collisionDispatcher, m_overlappingPairCache, m_impulseSolver, m_collisionConfig);
		m_world->setGravity(btVector3(0, -10, 0));

		// Setup rigidbody system.
		m_rigidbodySystem.Construct(ecsReg, this);
		m_physicsPipeline.RemoveSystem(m_rigidbodySystem);

		// connects a member function
		ecsReg.on_construct<LinaEngine::ECS::RigidbodyComponent>().connect<&PhysicsEngine::OnRigidbodyAdded>(this);
		ecsReg.on_destroy<LinaEngine::ECS::RigidbodyComponent>().connect<&PhysicsEngine::OnRigidbodyAdded>(this);
	}


	void PhysicsEngine::Tick(float fixedDelta)
	{
		// Physics simulation.
		m_world->stepSimulation(fixedDelta, 10);

		// Update system.
		m_physicsPipeline.UpdateSystems(fixedDelta);
	}

	void PhysicsEngine::CleanUp()
	{
	}

	void PhysicsEngine::OnRigidbodyAdded(entt::registry& reg, entt::entity ent)
	{
		btCollisionShape* colShape = nullptr;
		LinaEngine::ECS::RigidbodyComponent& rb = reg.get<LinaEngine::ECS::RigidbodyComponent>(ent);
		LinaEngine::ECS::TransformComponent& tr = reg.get<LinaEngine::ECS::TransformComponent>(ent);

		// Create collision shape depending on the type
		if (rb.m_collisionShape == LinaEngine::ECS::CollisionShape::BOX)
			colShape = new btBoxShape(btVector3(rb.m_halfExtents.x, rb.m_halfExtents.y, rb.m_halfExtents.z));
		else if (rb.m_collisionShape == LinaEngine::ECS::CollisionShape::SPHERE)
			colShape = new btSphereShape(btScalar(rb.m_radius));
		else if (rb.m_collisionShape == LinaEngine::ECS::CollisionShape::CAPSULE)
			colShape = new btCapsuleShape(btScalar(rb.m_radius), btScalar(rb.m_capsuleHeight));
		else if (rb.m_collisionShape == LinaEngine::ECS::CollisionShape::CYLINDER)
			colShape = new btCylinderShape(btVector3(rb.m_halfExtents.x, rb.m_halfExtents.y, rb.m_halfExtents.z));

		// Transformation
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(tr.transform.location.x, tr.transform.location.y, tr.transform.location.z));

		btScalar mass(rb.m_mass);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);

		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		rb.m_localInertia = Vector3(localInertia.getX(), localInertia.getY(), localInertia.getZ());

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		// Set the body in the map & assign rb component info.
		int id = LinaEngine::Utility::GetUniqueID();
		m_bodies[id] = body;
		rb.m_bodyID = id;
		
		// Add the body to world.
		m_world->addRigidBody(body);
	}

	void PhysicsEngine::OnRigidbodyRemoved(entt::registry& reg, entt::entity ent)
	{
		LinaEngine::ECS::RigidbodyComponent& rbComp = reg.get<LinaEngine::ECS::RigidbodyComponent>(ent);
		btRigidBody* rb = m_bodies[rbComp.m_bodyID];
		
		// delete motion state.
		if (rb->getMotionState())
			delete rb->getMotionState();

		// remove body.
		m_world->removeRigidBody(rb);

		// remove from the map.
		m_bodies.erase(rbComp.m_bodyID);
	}

}

