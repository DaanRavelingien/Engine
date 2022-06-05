#include "EnginePCH.h"
#include "SoundSystem.h"
#include <iostream>
#include "audio.c"

SoundSystem::SoundSystem()
{
	m_SoundThread = std::thread(&SoundSystem::HandleSoundQueue, this);
}

SoundSystem::~SoundSystem()
{
	m_ShuttingDown = true;
	m_SoundThread.join();
}

void SoundSystem::PlayMusic(const std::string& soundName, const float volume)
{
	SoundQueue sound{};
	sound.soundName = soundName;
	sound.volume = (int)volume;
	sound.isMusic = true;

	m_QueMutex.lock();
	m_SoundQueue.push(sound);
	m_QueMutex.unlock();
}

void SoundSystem::PlayASound(const std::string& soundName, const float volume)
{
	SoundQueue sound{};
	sound.soundName = soundName;
	sound.volume = (int)volume;
	sound.isMusic = false;

	m_QueMutex.lock();
	m_SoundQueue.push(sound);
	m_QueMutex.unlock();
}

void SoundSystem::HandleSoundQueue()
{
	while (!m_ShuttingDown)
	{
		SoundQueue sound{};

		m_QueMutex.lock();
		if (m_SoundQueue.size() > 0)
		{
			sound = m_SoundQueue.front();
			m_SoundQueue.pop();
		}
		m_QueMutex.unlock();

		if (!sound.soundName.empty())
		{
			if (sound.isMusic)
				this->PlayMusicSystemSpecific(sound.soundName, (float)sound.volume);
			else
				this->PlaySoundSystemSpecific(sound.soundName, (float)sound.volume);
		}
	}
}

bool SdlSoundSystem::m_Initialized{ false };

SdlSoundSystem::SdlSoundSystem()
{
	if (!m_Initialized)
	{
		initAudio();
		m_Initialized = true;
	}
}

SdlSoundSystem::~SdlSoundSystem()
{
	for (std::pair<std::string, Audio*> pair : m_Sounds)
	{
		freeAudio(pair.second);
	}

	if (m_Initialized)
	{
		endAudio();
		m_Initialized = false;
	}
}

void SdlSoundSystem::LoadSound(const std::string& soundName, const char* fileName, bool loop)
{
	Audio* audio{ createAudio(fileName,(uint8_t)loop,SDL_MIX_MAXVOLUME) };
	m_Sounds.emplace(soundName, audio);
}

void SdlSoundSystem::RemoveSound(const std::string& soundName)
{
	freeAudio(m_Sounds.at(soundName));
	m_Sounds.erase(soundName);
}

void SdlSoundSystem::PauseMusic()
{
	pauseAudio();
}

void SdlSoundSystem::ContiniuMusic()
{
	unpauseAudio();
}

void SdlSoundSystem::PlaySoundSystemSpecific(const std::string& soundName, const float volume)
{
	playSoundFromMemory(m_Sounds.at(soundName), (int)volume);
}

void SdlSoundSystem::PlayMusicSystemSpecific(const std::string& soundName, const float volume)
{
	playMusicFromMemory(m_Sounds.at(soundName), (int)volume);
}

LoggingSoundSystem::LoggingSoundSystem(SoundSystem* ss, bool muted)
	:m_pRealSs{ ss }
	, m_Muted{ muted }
{
}

LoggingSoundSystem::~LoggingSoundSystem()
{
	delete m_pRealSs;
	m_pRealSs = nullptr;
}

void LoggingSoundSystem::LoadSound(const std::string& soundName, const char* fileName, bool loop)
{
	m_pRealSs->LoadSound(soundName, fileName, loop);

	std::cout << "LoggingSoundSystem: Loading sound " << fileName << " as " << soundName << '\n';
}

void LoggingSoundSystem::RemoveSound(const std::string& soundName)
{
	m_pRealSs->RemoveSound(soundName);

	std::cout << "LoggingSoundSystem: Removing sound " << soundName << '\n';
}

void LoggingSoundSystem::PauseMusic()
{
	std::cout << "LoggingSoundSystem: paused music\n";
}

void LoggingSoundSystem::ContiniuMusic()
{
	std::cout << "LoggingSoundSystem: continiued music\n";

}

void LoggingSoundSystem::PlaySoundSystemSpecific(const std::string& soundName, const float volume)
{
	if (!m_Muted)
		m_pRealSs->PlayASound(soundName, volume);

	std::cout << "LoggingSoundSystem: Playing sound " << soundName << " at volume " << (int)volume << '\n';

}

void LoggingSoundSystem::PlayMusicSystemSpecific(const std::string& soundName, const float volume)
{
	if (!m_Muted)
		m_pRealSs->PlayMusic(soundName, volume);

	std::cout << "LoggingSoundSystem: Playing music " << soundName << " at volume " << (int)volume << '\n';
}

