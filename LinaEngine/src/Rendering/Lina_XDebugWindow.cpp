/*
Author: Inan Evin
www.inanevin.com

MIT License

Lina Engine, Copyright (c) 2018 Inan Evin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

4.0.30319.42000
9/30/2018 4:08:49 PM

*/

#include "pch.h"
#include "Rendering/Lina_XDebugWindow.hpp"

Lina_XDebugWindow::Lina_XDebugWindow() : Lina_XWindow()
{
	m_Window = NULL;
	m_Renderer = NULL;
}

Lina_XDebugWindow::~Lina_XDebugWindow()
{
	delete m_Renderer;
}

void Lina_XDebugWindow::InitWindow(int width, int height, const std::string& title)
{
	// Add a console message about correct initialization.
	Lina_Console cons = Lina_Console();
	cons.AddConsoleMsg("XDebugWindow initialized. (W: " + std::to_string(width) + " H: " + std::to_string(height) + ")", Lina_Console::MsgType::Initialization, "Window");

	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (m_Window != NULL)
	{
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (m_Renderer == NULL)
		{
			cons.AddConsoleMsg("SDL Renderer failed to initialize.", Lina_Console::MsgType::Error, "XDebugWindow");
			SDL_DestroyWindow(m_Window);
			m_Window = NULL;
		}
	}
	else
	{
		cons.AddConsoleMsg("SDL Window failed to initialize.", Lina_Console::MsgType::Error, "XDebugWindow");
	}

	m_IsClosed = false;
}

void Lina_XDebugWindow::Update()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	//Text rendering will come here.

	SDL_RenderPresent(m_Renderer);
}