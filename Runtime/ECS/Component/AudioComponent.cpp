#include <AudioComponent.hpp>

namespace Spore
{
	AudioComponent::AudioComponent()
	{
		m_name = "Audio";
		uint32 source = 0;
		m_source = source;
		alGenSources(1, &m_source);
	}

	AudioComponent::~AudioComponent()
	{
		m_audio_mapper.clear();
	}

	void AudioComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			if (ImGui::Button("Add Audio"))
			{
				Audio* audioTemp = AssetsManager::GetInstance().m_selected_audio;
				if (audioTemp != nullptr)
				{
					AddAudio(audioTemp);
				}
			}
			ImGui::PushID("Inspector::Audio::Play");
			if (ImGui::Button("Play"))
			{
				Play();
			}
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Audio::Pause");
			if (ImGui::Button("Pause"))
			{
				Pause();
			}
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID("Inspector::Audio::Stop");
			if (ImGui::Button("Stop"))
			{
				Stop();
			}
			ImGui::PopID();
			std::string imguiID = "";
			for (std::pair<std::string, Audio*> it_audio : m_audio_mapper)
			{
				ImGui::Text(it_audio.second->GetIdentifier().c_str());
				imguiID = "Inspector::Audio::" + it_audio.second->GetIdentifier() + "::Add To Buffer";
				ImGui::PushID(imguiID.c_str());
				if (ImGui::Button("Add To Buffer"))
				{
					alSourcei(m_source, AL_BUFFER, 0);
					m_buffer = alutCreateBufferFromFile(it_audio.second->GetPath().c_str());
					alSourcei(m_source, AL_BUFFER, m_buffer);
				}
				ImGui::PopID();
				ImGui::Separator();
			}
		}
	}

	void AudioComponent::AddAudio(Audio* p_audio)
	{
		m_audio_mapper.insert(std::make_pair(p_audio->GetIdentifier(), p_audio));
	}

	void AudioComponent::SetSource(uint32 p_source)
	{
		m_source = p_source;
		alGenSources(1, &m_source);
	}

	uint32 AudioComponent::GetSource()
	{
		return m_source;
	}

	void AudioComponent::SetBuffer(uint32 p_buffer)
	{
		m_buffer = p_buffer;
	}

	uint32 AudioComponent::GetBuffer()
	{
		return m_buffer;
	}

	void AudioComponent::Play()
	{
		m_pause_flag = false;
		m_stop_flag = false;
		alSourcePlay(m_source);
	}

	void AudioComponent::Pause()
	{
		if (!m_pause_flag)
		{
			alSourcePause(m_source);
			m_pause_flag = true;
		}
		else
		{
			alSourcePlay(m_source);
			m_pause_flag = false;
		}
	}

	void AudioComponent::Stop()
	{
		if (!m_stop_flag)
		{
			alSourceStop(m_source);
			m_stop_flag = true;
		}
	}
}