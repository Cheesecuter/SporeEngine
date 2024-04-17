#pragma once

#include <GraphicRenderer.hpp>
#include <AudioRenderer.hpp>

namespace Spore
{
	class Spore
	{
	public:
		Spore();
		~Spore();
		void Init();
		void Terminate();
	
	private:
		GraphicRenderer* m_graphic_renderer = nullptr;
		AudioRenderer* m_audio_renderer = nullptr;
	};
}