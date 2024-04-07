#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Types.hpp>
#include <Camera.hpp>
#include <Mouse.hpp>
#include <Scene.hpp>
#include <RenderPipeline.hpp>

namespace Spore
{
	class MainWindow
	{
	public:
		MainWindow(uint32 p_width, uint32 p_height, const char* p_windowID,
				   Camera* p_camera, RenderPipeline* p_render_pipeline);
		~MainWindow();

		GLFWwindow* m_window;
		Camera* m_camera;
		RenderPipeline* m_render_pipeline;
		const char* m_windowID;
		uint32 m_width, m_height;
		float32 m_last_x = (float32) (m_width / 2.0);
		float32 m_last_y = (float32) (m_height / 2.0);
		static bool m_camera_lock;
		static bool m_first_mouse;
		static bool m_hide_cursor;
		static std::map<GLFWwindow*, Camera*> m_camera_mapper;
		static std::map<std::string, Scene*> m_scene_mapper;

		void Terminate();
		uint32 GetWindowWidth();
		uint32 GetWindowHeight();
		void SetWindowSize(uint32 p_width, uint32 p_height);

	protected:

	private:
		GLFWwindow* InitWindow();
	};
}
