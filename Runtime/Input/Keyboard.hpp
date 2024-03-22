#pragma once
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <Types.hpp>
#include <SingletonInstance.hpp>
#include <Window.hpp>
#include <Camera.hpp>

namespace Spore
{
	class Keyboard : public Singleton<Keyboard>
	{
	public:
		void processInput(Spore::MainWindow* window,
						  Camera& camera, float32 deltaTime);

	private:
		Keyboard();
		~Keyboard();
		friend class Singleton<Keyboard>;
	};
}

#endif
