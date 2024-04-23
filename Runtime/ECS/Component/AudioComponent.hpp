#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <Types.hpp>
#include <Component.hpp>
#include <Audio.hpp>
#include <Texture.hpp>

namespace Spore
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent();
		virtual ~AudioComponent();

		virtual void InspectorPanel() override;
		void AddAudio(Audio* p_audio);
		void SetSource(uint32 p_source);
		uint32 GetSource();
		void SetBuffer(uint32 p_buffer);
		uint32 GetBuffer();
		void Play();
		void Pause();
		void Stop();

	protected:

	private:
		bool m_pause_flag = false;
		bool m_stop_flag = false;
		uint32 m_source;
		uint32 m_buffer;
		std::map<std::string, Audio*> m_audio_mapper;
		Texture* m_button_image_play;
		Texture* m_button_image_pause;
		Texture* m_button_image_stop;
	};
}