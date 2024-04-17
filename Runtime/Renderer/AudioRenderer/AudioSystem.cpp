#include <AudioSystem.hpp>

namespace Spore
{
	AudioSystem::AudioSystem()
	{

	}

	AudioSystem::~AudioSystem()
	{

	}

	void AudioSystem::Init()
	{
		alutInit(nullptr, nullptr);
	}

	void AudioSystem::Terminate()
	{
		alutExit();
	}

	void AudioSystem::SetSource(uint32 p_source)
	{
		m_source = p_source;
	}

	uint32 AudioSystem::GetSource()
	{
		return m_source;
	}

	void AudioSystem::SetListenerPosition(vec3f p_pos)
	{
		alListener3f(AL_POSITION, p_pos.x, p_pos.y, p_pos.z);
	}
}