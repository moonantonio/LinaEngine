/*
Author: Inan Evin
www.inanevin.com

BSD 2-Clause License
Lina Engine Copyright (c) 2018, Inan Evin All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.

-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO
-- THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
-- BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
-- GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
-- STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
-- OF SUCH DAMAGE.

4.0.30319.42000
9/30/2018 4:59:45 PM

*/

#pragma once

#ifndef Copy_Lina_Rendering_H
#define Copy_Lina_Rendering_H

//#include<list>
#include "Lina_Window.h"
#include "Lina_InputHandler.h"
#include "Lina_ExampleMesh.h"
#include "Lina_ExampleShader.h"
class Copy_Lina_Rendering
{

public:

	//static Lina_Rendering& Instance();
	void CreateDisplayWindow(int, int, const std::string&);
	void Render();
	void CleanUp();
	Copy_Lina_Rendering();
	Copy_Lina_Rendering(const std::shared_ptr<Lina_InputHandler>& inp);
	~Copy_Lina_Rendering();
	Copy_Lina_Rendering& operator= (const Copy_Lina_Rendering&);
	Copy_Lina_Rendering(const Copy_Lina_Rendering&);
	std::shared_ptr<Lina_Window> m_ActiveWindow;
	std::shared_ptr<Lina_InputHandler> inputEngine;

	void InitShaderAndMesh();

private:
	Lina_Mesh mesh;
	Lina_Shader shader;
};


#endif