#include <Spore.hpp>

namespace Spore
{
	Spore::Spore()
	{
		m_graphic_renderer = new GraphicRenderer();
		m_audio_renderer = new AudioRenderer();
	}

	Spore::~Spore()
	{
		delete m_audio_renderer;
		delete m_graphic_renderer;
	}

	void Spore::Init()
	{
		m_audio_renderer->GetAudioSystem()->Init();
	}

	void Spore::Terminate()
	{

	}
}