#include <AudioRenderer.hpp>

namespace Spore
{
	AudioRenderer::AudioRenderer()
	{
		m_audio_system = new AudioSystem();
	}

	AudioRenderer::~AudioRenderer()
	{
		delete m_audio_system;
	}

	AudioSystem* AudioRenderer::GetAudioSystem()
	{
		return m_audio_system;
	}
}