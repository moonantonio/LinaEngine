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

#pragma once

#include "pch.h"
#include "Audio/Lina_Sound.hpp"

Lina_Sound::Lina_Sound()
{
	m_Chunk = nullptr;
}

Lina_Sound::~Lina_Sound()
{
}

void Lina_Sound::LoadAudioChunk(const std::string file)
{
	std::string path = "./Resources/Sounds/" + file;

	//While the load function has the WAV keyword at the end, it can also load WAVE, OGG, MIDI and MP3.
	m_Chunk = Mix_LoadWAV(path.c_str());
}

void Lina_Sound::PlayAudioChunk()
{
	//Mixer function for playing sound.
	//There are 8 total sound channels in SDL_mixer, if we choose -1, SDL will use appropriate channel for the sound we want to played.
	//Second parameter is our actual sound data. Third parameter is for declaring how many times the sound will be played in a single call.
	Mix_PlayChannel(-1, m_Chunk, 0);
}

void Lina_Sound::CleanAudioChunk()
{
	if (m_Chunk != nullptr)
	{
		Mix_FreeChunk(m_Chunk);
		m_Chunk = nullptr;
	}
}
