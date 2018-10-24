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
#include "Rendering/Lina_XRenderWindow.hpp"

Lina_XRenderWindow::Lina_XRenderWindow() : Lina_XWindow()
{
	m_Window = NULL;
}

Lina_XRenderWindow::~Lina_XRenderWindow()
{
}

void Lina_XRenderWindow::InitWindow(int width, int height, const std::string& title)
{
	// Add a console message about correct initialization.
	Lina_Console cons = Lina_Console();
	cons.AddConsoleMsg("XRenderWindow initialized. (W: " + std::to_string(width) + " H: " + std::to_string(height) + ")", Lina_Console::MsgType::Initialization, "Window");

	// Set additional parameters for SDL window using SDL_WINDOW_OPENGL
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	// 8 bits (at least) -> 2 to the pow of 8 amount of color data. 256.
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);	// 8 bits -> 2 to the pow of 8 amount of color data. 256.
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);	// 8 bits -> 2 to the pow of 8 amount of color data. 256.
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);	// 8 bits -> 2 to the pow of 8 amount of color data. 256.
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	// How much data will SDL allocate for a single pixel.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	// Alloc an area for 2 blocks of display mem.


													// Create an SDL window.
	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	/* SDL -> Goes to OS, asks a window with the params. But we can not draw via OpenGL on the returned window bc OS has control over it.
	That's where the GL context comes into play. Reduces the control of OS over a window, so SDL -> Goes to OS, OS -> goes to GPU while
	OpenGL commands the GPU about this transfer, then GPU initalizes the window so that it can draw on it using openGL commands.
	*/

	// We create a context using our window, so we will have power over our window via OpenGL -> GPU.
	m_glContext = SDL_GL_CreateContext(m_Window);

	// Disable vsync. Needs to be called after SDL_GL_CreateContext bc swap interval works on the current active context. ( can be changed laterwards )
	SDL_GL_SetSwapInterval(0);

	// Initialize GLEW.
	GLenum status = glewInit();

	// Check glew initialization status.
	if (status != GLEW_OK)
		cons.AddConsoleMsg("Glew failed to initialize!", Lina_Console::MsgType::Error, "Window");
	else
		cons.AddConsoleMsg("Glew initialized.", Lina_Console::Initialization, "Window");

	// Set closed flag. This will be checked by OS events being received on Update.
	m_IsClosed = false;
}

void Lina_XRenderWindow::Update()
{
	SDL_GL_SwapWindow(m_Window);
}
