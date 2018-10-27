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

#pragma once

#ifndef Lina_EditorWindow_HPP
#define Lina_EditorWindow_HPP

#include <SDL2/SDL.h>
#include <string>

class Lina_EditorWindow
{
public:
	Lina_EditorWindow(int, int, const std::string&);
	~Lina_EditorWindow();

	void Update();
	void CloseWindow();
	void HandleInputs();
	void Run();
	void Cleanup();

	bool IsClosed() { return b_IsClosed; }
	int GetWidth() const { return m_ScreenHeight; }
	int GetHeight() const { return m_ScreenHeight; }
	std::string GetTitle() { return m_Title; }

	void operator=(const Lina_EditorWindow& other) {}
private:
	SDL_Window* m_Window;
	bool b_IsClosed;
	int m_ScreenWidth;
	int m_ScreenHeight;
	std::string m_Title;
};

#endif