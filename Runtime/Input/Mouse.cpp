#include <Mouse.hpp>

namespace Spore
{
	Mouse::Mouse()
	{
		m_x_offset = 0; m_y_offset = 0;
		m_last_x = 0; m_last_y = 0;
		m_button_left = 0; m_button_right = 0;
	}

	Mouse::~Mouse()
	{
	}

	void Mouse::Update()
	{
		m_x_offset = m_x_pos - m_last_x;
		m_y_offset = m_last_y - m_y_pos;
		m_last_x = m_x_pos;
		m_last_y = m_y_pos;
	}
}