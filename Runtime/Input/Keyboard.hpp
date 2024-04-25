#pragma once

#include <Types.hpp>
#include <SingletonInstance.hpp>
#include <KeyboardKeys.h>
//#include <Window.hpp>
#include <Camera.hpp>

namespace Spore
{
	class MainWindow;

	class Keyboard : public Singleton<Keyboard>
	{
	public:
		void SetWindow(MainWindow* p_window);
		MainWindow* GetWindow();
		int32 processInput(MainWindow* p_window,
						  Camera& p_camera, float32 p_delta_time);
		int32 GetKey(MainWindow* p_window);

	protected:

	private:
		Keyboard();
		~Keyboard();
		MainWindow* m_window = nullptr;
		friend class Singleton<Keyboard>;
	};
}
