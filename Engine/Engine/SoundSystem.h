#pragma once
#define UNREFERENCED_PARAMETER(P) (P)
#include <map>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include "audio.h"

class SoundSystem
{
public:
	virtual ~SoundSystem();

	void PlayMusic(const std::string& soundName, const float volume);
	void PlayASound(const std::string& soundName, const float volume);

	virtual void LoadSound(const std::string& soundName, const char* fileName, bool loop = false) = 0;
	virtual void RemoveSound(const std::string& soundName) = 0;

protected:
	SoundSystem();

	virtual void PlaySoundSystemSpecific(const std::string& soundName, const float volume) = 0;
	virtual void PlayMusicSystemSpecific(const std::string& soundName, const float volume) = 0;

private:
	struct SoundQueue
	{
		std::string soundName{};
		int volume{ 0 };
		bool isMusic{ false };
	};

	std::atomic_bool m_ShuttingDown{ false };
	std::mutex m_QueMutex{};
	std::thread m_SoundThread;
	std::queue<SoundQueue> m_SoundQueue{};

	void HandleSoundQueue();
};

class NullSoundSystem final : public SoundSystem
{
private:
	void LoadSound(const std::string& soundName, const char* fileName, bool loop = false)
	{
		UNREFERENCED_PARAMETER(soundName);
		UNREFERENCED_PARAMETER(fileName);
		UNREFERENCED_PARAMETER(loop);
	};
	void RemoveSound(const std::string& soundName)
	{
		UNREFERENCED_PARAMETER(soundName);
	};
	void PlaySoundSystemSpecific(const std::string& soundName, const float volume)
	{
		UNREFERENCED_PARAMETER(soundName);
		UNREFERENCED_PARAMETER(volume);
	};
	void PlayMusicSystemSpecific(const std::string& soundName, const float volume)
	{
		UNREFERENCED_PARAMETER(soundName);
		UNREFERENCED_PARAMETER(volume);
	};
};

class SdlSoundSystem final : public SoundSystem
{
public:
	SdlSoundSystem();
	~SdlSoundSystem();

	void LoadSound(const std::string& soundName, const char* fileName, bool loop = false);
	void RemoveSound(const std::string& soundName);

protected:
	void PlaySoundSystemSpecific(const std::string& soundName, const float volume);
	void PlayMusicSystemSpecific(const std::string& soundName, const float volume);

	std::map<std::string, Audio*> m_Sounds{};
};

class LoggingSoundSystem final : public SoundSystem
{
public:
	LoggingSoundSystem(SoundSystem* ss, bool muted = false);
	~LoggingSoundSystem();

	void LoadSound(const std::string& soundName, const char* fileName, bool loop = false);
	void RemoveSound(const std::string& soundName);
protected:
	void PlaySoundSystemSpecific(const std::string& soundName, const float volume);
	void PlayMusicSystemSpecific(const std::string& soundName, const float volume);

	SoundSystem* m_pRealSs;
	bool m_Muted{ false };
};

