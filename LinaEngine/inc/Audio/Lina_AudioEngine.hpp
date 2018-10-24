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

#ifndef Lina_AudioEngine_HPP
#define Lina_AudioEngine_HPP

#include <SDL2/SDL_mixer.h>

#include <Core/Lina_ObjectHandler.hpp>

class Lina_AudioEngine
{
public:
	Lina_AudioEngine();
	~Lina_AudioEngine();

	void Init();
	void LoadMusic(const std::string file);
	void LoadAudioChunk(const std::string file);
	void PlayAudioChunk();
	void PlayMusic();
	void HaltMusic();
	void PauseMusic();
	void ResumeMusic();

	//Lina_ObjectHandler eventHandler;

private:
	Mix_Chunk* m_Chunk;
	Mix_Music* m_Music;

	bool b_IsMusicPlaying;
	bool b_IsMusicPaused;
};

#endif