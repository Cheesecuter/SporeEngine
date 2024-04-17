#pragma once

#include <AudioSystem.hpp>

namespace Spore
{
	class AudioRenderer
	{
	public:
		AudioRenderer();
		~AudioRenderer();
		AudioSystem* GetAudioSystem();

	private:
		AudioSystem* m_audio_system = nullptr;
	};
}