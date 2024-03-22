#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

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
		MainWindow(uint32 width_p, uint32 height_p, const char* windowID_p,
				   Camera* camera_p, RenderPipeline* renderPipeline_p);
		~MainWindow();

		GLFWwindow* window;
		Camera* camera;
		RenderPipeline* renderPipeline;
		const char* windowID;
		uint32 width, height;
		float32 lastX = (float32) (width / 2.0);
		float32 lastY = (float32) (height / 2.0);
		static bool cameraLock;
		static bool firstMouse;
		static bool hideCursor;
		static std::map<GLFWwindow*, Camera*> cameraMapper;
		static std::map<std::string, Scene*> sceneMapper;

		void WindowTerminate();
		uint32 GetWindowWidth();
		uint32 GetWindowHeight();
		void SetWindowSize(uint32 width_p, uint32 height_p);

	protected:

	private:
		GLFWwindow* InitWindow();
	};
}

#endif
