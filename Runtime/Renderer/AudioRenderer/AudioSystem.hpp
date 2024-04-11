#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <Types.hpp>

namespace Spore
{
	class AudioSystem
	{
	public:
		AudioSystem();
		~AudioSystem();

		void Init();
		void Terminate();
		void SetSource(uint32 p_source);
		uint32 GetSource();

	protected:

	private:
		uint32 m_source;
	};
}