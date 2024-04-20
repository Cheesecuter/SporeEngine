#pragma once

#include <AudioSystem.hpp>

namespace Spore
{
	class AudioRenderer
	{
	public:
		AudioRenderer();
		~AudioRenderer();
		void Init();
		void Terminate();
		AudioSystem* GetAudioSystem();

	private:
		AudioSystem* m_audio_system = nullptr;
	};
}