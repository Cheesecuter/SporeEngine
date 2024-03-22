#pragma once
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <Types.hpp>
#include <SingletonInstance.hpp>

namespace Spore
{
	class Mouse : public Singleton<Mouse>
	{
	public:
		float32 xPos;
		float32 yPos;
		float32 xOffset;
		float32 yOffset;
		float32 lastX;
		float32 lastY;
		bool buttonLeft;
		bool buttonRight;
		void Update();

	private:
		Mouse();
		~Mouse();
		friend class Singleton<Mouse>;
	};
}

#endif
