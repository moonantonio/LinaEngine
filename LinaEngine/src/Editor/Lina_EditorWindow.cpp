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
10/20/2018 7:39:33 PM

*/

#include "pch.h"
#include "Editor/Lina_EditorWindow.hpp"

Lina_EditorWindow::Lina_EditorWindow(int width, int height, const std::string& title):
m_ScreenWidth(width),
m_ScreenHeight(height),
m_Title(title),
b_IsClosed(false)
{
	Lina_Console cons = Lina_Console();
	cons.AddConsoleMsg("Editor Window Initialized", Lina_Console::MsgType::Initialization, "Lina Editor");

	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_SHOWN);
	if (!m_Window)
	{
		cons.AddConsoleMsg("Editor Window failed to initialize", Lina_Console::MsgType::Error, "Lina Editor");
	}

	Run();
}

Lina_EditorWindow::~Lina_EditorWindow()
{
}

void Lina_EditorWindow::Update()
{
	//TODO: Decide what to do in here.
}

void Lina_EditorWindow::CloseWindow()
{
	b_IsClosed = true;
}

void Lina_EditorWindow::HandleInputs()
{
	SDL_Event e;
	while (b_IsClosed == false)
	{
		if(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				CloseWindow();
				Cleanup();
			}
		}
	}
}

void Lina_EditorWindow::Run()
{
	HandleInputs();

	//TODO: Decide what to do with update.
	//Update();
}

void Lina_EditorWindow::Cleanup()
{
	Lina_Console cons = Lina_Console();
	cons.AddConsoleMsg("Editor Window Deinitialized", Lina_Console::MsgType::Deinitialization, "Lina Editor");

	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}
