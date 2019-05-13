/*
Author: Inan Evin
www.inanevin.com

Copyright 2018 Inan Evin

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions
and limitations under the License.

Class: RenderEngine
Timestamp: 4/15/2019 12:26:31 PM

*/

#pragma once

#ifndef RenderEngine_HPP
#define RenderEngine_HPP

#include "Rendering/Sampler.hpp"
#include "Rendering/ArrayBitmap.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/RenderTarget.hpp"
#include "Rendering/GameRenderContext.hpp"
#include "Rendering/RenderableObjectData.hpp"
#include "ECS/EntityComponentSystem.hpp"
#include "ECS/Systems/CameraSystem.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Systems/MeshRendererSystem.hpp"
#include "ECS/Systems/SpriteRendererSystem.hpp"
#include "ECS/Systems/LightingSystem.hpp"


using namespace LinaEngine::ECS;
using namespace LinaEngine;

namespace LinaEngine::Graphics
{

	class RenderEngine
	{
	public:

		RenderEngine();

		~RenderEngine();

		FORCEINLINE void* GetNativeWindow()
		{
			return m_RenderDevice->GetNativeWindow();
		}

		// Create a render context.
		FORCEINLINE bool CreateContextWindow()
		{
			return m_RenderDevice->CreateContextWindow();
		};

		// Set the target of the callbacks coming from the main window context.
		FORCEINLINE void SetMainWindowEventCallback(const std::function<void(Event&)>& callback)
		{
			m_RenderDevice->SetMainWindowEventCallback(callback);
		}

		// Sets the current active ambient light in the level.
		FORCEINLINE void SetAmbientLight(AmbientLight light)
		{
			m_LightingSystem.SetAmbientLight(light);
		}


		// Initialize the render renderEngine.
		void Initialize(EntityComponentSystem* ecsIn);

		// Called each frame.
		void Tick(float delta);

		// Called when the main window is resized.
		void OnWindowResized(float width, float height);

		// Load a texture resource to be loaded.
		LINA_API Texture& LoadTextureResource(const LinaString& fileName, PixelFormat internalPixelFormat, bool generateMipMaps, bool compress);

		// Feed a model resource to be loaded.
		LINA_API RenderableObjectData& LoadModelResource(const LinaString& fileName);

		// Loads a skybox texture resource w/ 6 faces.
		LINA_API Texture& LoadCubemapTextureResource(const LinaString& filePosX, const LinaString& fileNegX, const LinaString& filePosY, const LinaString& fileNegY, const LinaString& filePosZ, const LinaString& fileNegZ);

		// Adds the targeted resource to the garbage collection dump.
		LINA_API void UnloadTextureResource(Texture& textureResource);

		//  Adds the targeted resource to the garbage collection dump.
		LINA_API void UnloadModelResource(RenderableObjectData& modelResource);


	private:

		// clears resource memory.
		void DumpMemory();

		// Renders skybox
		void RenderSkybox();

	private:

		// Device for rendering operations.
		std::unique_ptr<PAMRenderDevice> m_RenderDevice;

		// ECS reference.
		EntityComponentSystem* m_ECS;

		// Default texture sampler
		Sampler m_DefaultSampler;

		// Skybox texture sampler
		Sampler m_SkyboxSampler;

		// Default texture data.
		ArrayBitmap m_DefaultTextureBitmap;

		// Default diffuse texture
		Texture m_DefaultDiffuseTexture;

		// Default skybox texture
		Texture m_SkyboxTexture;

		// Default shader
		Shader m_BasicStandardShader;

		// Skybox shader
		Shader m_BasicSkyboxShader;

		// Default render target
		RenderTarget m_RenderTarget;

		// Default drawing parameters.
		DrawParams m_DefaultDrawParams;

		// Skybox drawing parameters.
		DrawParams m_SkyboxDrawParams;

		// Sprite drawing parameters.
		DrawParams m_SpriteDrawParams;

		// Default camera perspective
		Matrix m_CurrentProjectionMatrix;

		// Default Game Render Context
		GameRenderContext m_DefaultRenderContext;

		// ECS system for rendering camera perspective.
		CameraSystem m_CameraSystem;

		// ECS system for drawing meshes.
		MeshRendererSystem m_MeshRendererSystem;

		// ECS system for handling scene lighting.
		LightingSystem m_LightingSystem;

		// ECS system list for rendering operations.
		ECSSystemList m_RenderingPipeline;

		// Default camera data struct
		CameraComponent m_ActiveCameraComponent;

		// Texture resources.
		LinaArray<Texture*> m_TextureResources;

		// Model resources
		LinaArray<RenderableObjectData*> m_RenderableObjectDataResources;

		// Dumped data to be cleared by garbage collector.
		LinaArray<Texture*> m_TextureDump;
		LinaArray<RenderableObjectData*> m_RenderableObjectDataDump;

	private:

		// Standart Skybox vertex array object.
		uint32 m_SkyboxVAO;

		// Standart sprite vertex array object.
		uint32 m_SpriteVAO;
	};

}


#endif