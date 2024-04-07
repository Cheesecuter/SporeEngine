#pragma once

#include <Types.hpp>
#include <SingletonInstance.hpp>

namespace Spore
{
	class Mouse : public Singleton<Mouse>
	{
	public:
		float32 m_x_pos;
		float32 m_y_pos;
		float32 m_x_offset;
		float32 m_y_offset;
		float32 m_last_x;
		float32 m_last_y;
		bool m_button_left;
		bool m_button_right;

		void Update();

	protected:

	private:
		Mouse();
		~Mouse();
		friend class Singleton<Mouse>;
	};
}
