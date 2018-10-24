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
#include "Audio/Lina_AudioEngine.hpp"

Lina_AudioEngine::Lina_AudioEngine()
{
	sound = new Lina_Sound;
	music = new Lina_Music;
}

Lina_AudioEngine::~Lina_AudioEngine()
{
	Lina_Console cons = Lina_Console();
	cons.AddConsoleMsg("Audio engine deinitialized.", Lina_Console::MsgType::Deinitialization, "Audio Engine");
}

void Lina_AudioEngine::Init()
{
	Lina_Console cons = Lina_Console();
	cons.AddConsoleMsg("Audio engine initialized.", Lina_Console::MsgType::Initialization, "Audio Engine");

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		std::cout << "wtf";
	}
}

void Lina_AudioEngine::LoadMusic(const std::string file)
{
	//std::string path = "./Resources/Musics/" + file;

	//m_Music = Mix_LoadMUS(path.c_str());

	music->LoadMusic(file);
}

void Lina_AudioEngine::LoadAudioChunk(const std::string file)
{
	//std::string path = "./Resources/Sounds/" + file;

	//m_Chunk = Mix_LoadWAV(path.c_str());

	sound->LoadAudioChunk(file);
}

void Lina_AudioEngine::PlayAudioChunk()
{
	sound->PlayAudioChunk();
}

void Lina_AudioEngine::PlayMusic()
{
	music->PlayMusic();
}

void Lina_AudioEngine::HaltMusic()
{
	music->HaltMusic();
}

void Lina_AudioEngine::PauseMusic()
{
	music->PauseMusic();
}

void Lina_AudioEngine::ResumeMusic()
{
	music->ResumeMusic();
}

void Lina_AudioEngine::CleanUp()
{
	sound->CleanAudioChunk();
	music->CleanMusic();

	delete sound;
	delete music;
}
