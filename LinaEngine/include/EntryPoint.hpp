/*
Author: Inan Evin
www.inanevin.com

Copyright 2018 Inan Evin

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
and limitations under the License.

Class: Lina_EntryPoint
Timestamp: 12/29/2018 11:28:02 PM

*/

#pragma once


#ifdef LINA_PLATFORM_WINDOWS

#include "Core/Application.hpp"
#include "Utility/Log.hpp"

extern LinaEngine::Application* LinaEngine::CreateApplication();

int main(int argc, char** argv)
{
	LinaEngine::Log::Init();	
	auto app = LinaEngine::CreateApplication();
	delete app;
}

#endif


