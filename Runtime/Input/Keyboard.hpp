#pragma once

#include <Types.hpp>
#include <SingletonInstance.hpp>
#include <Window.hpp>
#include <Camera.hpp>

namespace Spore
{
	class Keyboard : public Singleton<Keyboard>
	{
	public:
		void processInput(Spore::MainWindow* p_window,
						  Camera& p_camera, float32 p_delta_time);

	protected:

	private:
		Keyboard();
		~Keyboard();
		friend class Singleton<Keyboard>;
	};
}
