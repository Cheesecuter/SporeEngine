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

	public:

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

	public:
		/**
		 * @brief Render the inspector panel for the audio component.
		 *
		 * This function renders the inspector panel for the audio component using ImGui.
		 * It allows users to add audio files, control playback (play, pause, stop), and manage audio buffers.
		 */
		virtual void InspectorPanel() override;
		/**
		 * @brief Add an audio object to the audio component.
		 *
		 * This function adds an audio object to the audio component's mapper.
		 *
		 * @param p_audio Pointer to the audio object to add.
		 */
		void AddAudio(Audio* p_audio);
		/**
		 * @brief Set the audio source for the audio component.
		 *
		 * This function sets the audio source for the audio component and generates the source.
		 *
		 * @param p_source The audio source ID to set.
		 */
		void SetSource(uint32 p_source);
		/**
		 * @brief Get the audio source ID associated with the audio component.
		 *
		 * @return The audio source ID associated with the audio component.
		 */
		uint32 GetSource();
		/**
		 * @brief Set the audio buffer for the audio component.
		 *
		 * This function sets the audio buffer for the audio component.
		 *
		 * @param p_buffer The audio buffer ID to set.
		 */
		void SetBuffer(uint32 p_buffer);
		/**
		 * @brief Get the audio buffer ID associated with the audio component.
		 *
		 * @return The audio buffer ID associated with the audio component.
		 */
		uint32 GetBuffer();
		/**
		 * @brief Start playing the audio associated with the audio component.
		 *
		 * This function starts playing the audio associated with the audio component.
		 */
		void Play();
		/**
		 * @brief Pause or resume the playback of the audio associated with the audio component.
		 *
		 * This function pauses or resumes the playback of the audio associated with the audio component.
		 */
		void Pause();
		/**
		 * @brief Stop the playback of the audio associated with the audio component.
		 *
		 * This function stops the playback of the audio associated with the audio component.
		 */
		void Stop();

	protected:

	private:

	};
}