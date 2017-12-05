#include "AudioMaster.hpp"
#include <iostream>
#include <stdlib.h>
namespace ThrashEngine {
	AudioMaster::AudioMaster()
	{
		m_device = nullptr;
	}
	AudioMaster::~AudioMaster()
	{

	}
	ResultState AudioMaster::Init()
	{
		m_device = alcOpenDevice(NULL);
		if (!m_device)
		{
			std::cout << "Failed to open device" << std::endl;
			return ResultState::Fail;
		}
		ALboolean enumeration;

		enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
		if (enumeration == AL_FALSE)
			std::cout << "Enumeration not supported" << std::endl;
		else
			std::cout << "Enumeration supported" << std::endl;

		if(enumeration)
			list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

		ALCenum error;

		error = alGetError();
		if (error != AL_NO_ERROR)
			std::cout << "Sound Error happened!" << std::endl;

		m_context = alcCreateContext(m_device, NULL);
		if (!alcMakeContextCurrent(m_context))
			// failed to make context current
			// test for errors here using alGetError();

		return ResultState::Success;
	}

	void AudioMaster::list_audio_devices(const ALCchar *devices)
	{
		const ALCchar *device = devices, *next = devices + 1;
		size_t len = 0;

		fprintf(stdout, "Devices list:\n");
		fprintf(stdout, "----------\n");
		while (device && *device != '\0' && next && *next != '\0') {
			fprintf(stdout, "%s\n", device);
			len = strlen(device);
			device += (len + 1);
			next += (len + 2);
		}
		fprintf(stdout, "----------\n");
	}



	SoundBuffer::SoundBuffer() {}
	SoundBuffer::~SoundBuffer(){}
	int SoundBuffer::LoadWav(std::string str)
	{
		//Some data for wav
		char type[4];
		DWORD size, chunkSize;
		short formatType, channels;
		DWORD sampleRate, avgBytesPerSec;
		short bytesPerSample, bitsPerSample;
		DWORD dataSize;

		
		//Open file
		FILE* fp = NULL;
		fp = fopen(str.c_str(), "rb");

		fread(type, sizeof(char), 4, fp);
		fread(&size, sizeof(DWORD), 1, fp);
		fread(type, sizeof(char), 4, fp);
		fread(type, sizeof(char), 4, fp);

		fread(&chunkSize, sizeof(DWORD), 1, fp);
		fread(&formatType, sizeof(short), 1, fp);
		fread(&channels, sizeof(short), 1, fp);
		fread(&sampleRate, sizeof(DWORD), 1, fp);
		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
		fread(&bytesPerSample, sizeof(short), 1, fp);
		fread(&bitsPerSample, sizeof(short), 1, fp);
		fread(type, sizeof(char), 4, fp);
		fread(&dataSize, sizeof(DWORD), 1, fp);

		unsigned char* buf = new unsigned char[dataSize];
		fread(buf, sizeof(BYTE), dataSize, fp);

		ALuint frequency = sampleRate;
		ALenum format = 0;
		alGenBuffers(1, &m_bufferId);

		if (bitsPerSample == 8)
		{
			if (channels == 1)
			{
				format = AL_FORMAT_MONO8;
			}
			else if (channels == 2)
			{
				format = AL_FORMAT_STEREO8;
			}
		}
		else if (bitsPerSample == 16)
		{
			if (channels == 1)
			{
				format = AL_FORMAT_MONO16;
			}
			else if (channels == 2)
			{
				format = AL_FORMAT_STEREO16;
			}
		}
		fclose(fp);
		alBufferData(m_bufferId, format, buf, dataSize, frequency);
		delete[] buf;
		return 1;

	}
	int SoundBuffer::GetBuffer()
	{
		return m_bufferId;
	}

	SoundSource::SoundSource()
	{

		alGenSources((ALuint)1, &m_sourceId);
		// check for errors
		alSourcef(m_sourceId, AL_PITCH, 1);
		// check for errors
		alSourcef(m_sourceId, AL_GAIN, 1);
		// check for errors
		alSource3f(m_sourceId, AL_POSITION, 0, 0, 0);
		// check for errors
		alSource3f(m_sourceId, AL_VELOCITY, 0, 0, 0);
		// check for errors
		alSourcei(m_sourceId, AL_LOOPING, AL_FALSE);
		// check for errros

	}
	SoundSource::~SoundSource()
	{
		//alDeleteSources(1, &m_sourceId);
	}
	void SoundSource::SetBuffer(SoundBuffer* buf)
	{
		m_buffer = buf;
		alSourcei(m_sourceId, AL_BUFFER, buf->GetBuffer());
		// check for errors
	}
	void SoundSource::Play(bool weakness)
	{

		m_weak = weakness;
		if (!isPlaying()) alSourcePlay(m_sourceId);
	}
	void SoundSource::Pause()
	{
		if (isPlaying()) alSourcePause(m_sourceId);
	}
	void SoundSource::Stop()
	{
		if (isPlaying()) alSourceStop(m_sourceId);
	}
	bool SoundSource::isPlaying()
	{
		ALenum state;

		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);

		return (state == AL_PLAYING);
	}
	bool SoundSource::isWeak()
	{
		return m_weak;
	}
	ALuint SoundSource::GetSource()
	{
		return m_sourceId;
	}

	
	SoundManager::SoundManager()
	{
		m_sources.clear();
	}
	SoundManager::~SoundManager()
	{
	//	for (auto i = m_sources.begin(); i != m_sources.end();i++)
			m_sources.clear();
	}
	void SoundManager::Play(SoundSource* source)
	{

		m_sources.push_back(source);
		source->Play();
	}
	void SoundManager::Pause()
	{
		for (auto i = m_sources.begin(); i != m_sources.end(); i++)
		{
			(*i)->Pause();
		}
	}
	std::list<SoundSource*>* SoundManager::GetSounds()
	{
		return &m_sources;
	}
	void SoundManager::Update()
	{
		std::list<std::list<SoundSource*>::iterator> deleteSounds;

		for (auto i = m_sources.begin(); i != m_sources.end(); i++)
		{
			if ((*i)->isWeak() && !(*i)->isPlaying())
			{
				(*i)->Stop();
				deleteSounds.push_back(i);
			}
		}
		for (auto i = deleteSounds.begin(); i != deleteSounds.end(); i++)
		{
			m_sources.erase(*i);
		}
	}


}