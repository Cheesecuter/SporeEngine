#include <AudioRenderer.hpp>

namespace Spore
{
	AudioRenderer::AudioRenderer()
	{

	}

	AudioRenderer::~AudioRenderer()
	{

	}

	void AudioRenderer::Init()
	{
		m_audio_system = new AudioSystem();
	}
	
	void AudioRenderer::Terminate()
	{
		delete m_audio_system;
	}

	AudioSystem* AudioRenderer::GetAudioSystem()
	{
		return m_audio_system;
	}
}