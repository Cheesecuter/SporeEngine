#pragma once

#include <Types.hpp>
#include <Camera.hpp>
#include <Mouse.hpp>
#include <Scene.hpp>
#include <RenderPipeline.hpp>

namespace Spore
{
	class GraphicRenderer;

	class MainWindow
	{
	public:
		MainWindow(uint32 p_width, uint32 p_height, const char* p_windowID,
				   Camera* p_camera, RenderPipeline* p_render_pipeline);
		~MainWindow();

		const char* m_windowID;
		static bool m_camera_lock;
		static bool m_first_mouse;
		static bool m_hide_cursor;
		static Camera* m_camera;
		static std::map<std::string, Scene*> m_scene_mapper;

		void Init();
		void Terminate();
		void SetWindowSize(uint32 p_width, uint32 p_height);
		uint32 GetWindowWidth();
		uint32 GetWindowHeight();
		void SetCamera(Camera* p_camera);
		Camera* GetCamera();
		bool TransformCamera(float32 p_delta_time);
		void SetWindow(GLFWwindow* p_window);
		GLFWwindow* GetWindow();
		void SetGraphicRenderer(GraphicRenderer* p_graphic_renderer);
		GraphicRenderer* GetGraphicRenderer();
		RenderPipeline* GetRenderPipeline();

	protected:

	private:
		uint32 m_width, m_height;
		GLFWwindow* m_window;
		GraphicRenderer* m_graphic_renderer;

		GLFWwindow* InitWindow();
	};
}
