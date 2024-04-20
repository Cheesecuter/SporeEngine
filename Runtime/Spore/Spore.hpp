#pragma once

#include <GraphicRenderer.hpp>
#include <AudioRenderer.hpp>
#include <Window.hpp>
#include <UI.hpp>
#include <PhysicSystem.hpp>

namespace Spore
{
	class _Spore
	{
	public:
		_Spore();
		~_Spore();
		void Init();
		void PreProcessing();
		void Runtime();
		void Terminate();
	
	private:
		GraphicRenderer* m_graphic_renderer = nullptr;
		AudioRenderer* m_audio_renderer = nullptr;
		MainWindow* m_window = nullptr;
		UI* m_ui = nullptr;
		PhysicSystem* m_physicSystem = nullptr;
		Serializer* m_serializer = nullptr;

		uint32 SCREEN_WIDTH = 1200;
		uint32 SCREEN_HEIGHT = 900;
	};
}