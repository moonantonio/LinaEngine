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


*/

#include "pch.h"
#include <Audio/Lina_Music.hpp>

Lina_Music::Lina_Music()
{
	m_Music = nullptr;
}

Lina_Music::~Lina_Music()
{
}

void Lina_Music::LoadMusic(std::string file)
{
	std::string path = "./Resources/Musics/" + file;

	m_Music = Mix_LoadMUS(path.c_str());
}

void Lina_Music::PlayMusic()
{
	Mix_PlayMusic(m_Music, -1);
}

void Lina_Music::HaltMusic()
{
	Mix_HaltMusic();
}

void Lina_Music::ResumeMusic()
{
	Mix_ResumeMusic();
}

void Lina_Music::PauseMusic()
{
	Mix_PauseMusic();
}

void Lina_Music::CleanMusic()
{
	if (m_Music != nullptr)
	{
		Mix_FreeMusic(m_Music);
		m_Music = nullptr;
	}
}
