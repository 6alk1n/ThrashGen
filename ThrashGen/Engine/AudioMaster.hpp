#pragma once
#include "Core.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <list>
namespace ThrashEngine
{
	class AudioMaster {
	public:
		AudioMaster();
		~AudioMaster();
		ResultState Init();
	protected:

		void list_audio_devices(const ALCchar *devices);

		ALCdevice* m_device;
		ALCcontext* m_context;
	};

	class SoundBuffer
	{
	public:
		SoundBuffer();
		~SoundBuffer();
		int LoadWav(std::string);
		int GetBuffer();
	protected:
		ALuint m_bufferId;
	};

	class  SoundSource
	{
	public:
		SoundSource();
		~SoundSource();
		void SetBuffer(SoundBuffer*);
		void Play(bool weakness=true);
		void Pause();
		void Stop();
		bool isPlaying();
		bool isWeak();
		ALuint GetSource();
	protected:
		SoundBuffer* m_buffer;
		ALuint m_sourceId;
		bool m_weak;
	};

	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();
		void Play(SoundSource*);
		void Pause();
		std::list<SoundSource*>* GetSounds();
		void Update();
	protected:
		std::list<SoundSource*> m_sources;
	};


}