#include <AudioComponent.hpp>

namespace Spore
{
	AudioComponent::AudioComponent()
	{
		m_name = "Audio";
	}

	AudioComponent::~AudioComponent()
	{

	}

	void AudioComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			if (ImGui::Button("Play"))
			{
				Play();
			}
			if (ImGui::Button("Pause"))
			{
				Pause();
			}
			if (ImGui::Button("Stop"))
			{
				Stop();
			}
		}
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