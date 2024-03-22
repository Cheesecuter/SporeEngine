#include <Mouse.hpp>

namespace Spore
{
	Mouse::Mouse()
	{
		xOffset = 0; yOffset = 0;
		lastX = 0; lastY = 0;
		buttonLeft = 0; buttonRight = 0;
	}

	Mouse::~Mouse()
	{
	}

	void Mouse::Update()
	{
		xOffset = xPos - lastX;
		yOffset = lastY - yPos;
		lastX = xPos;
		lastY = yPos;
	}
}