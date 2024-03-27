#include <Window.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>

namespace Spore
{
	std::map<GLFWwindow*, Camera*> MainWindow::cameraMapper;
	std::map<std::string, Scene*> MainWindow::sceneMapper;
	bool MainWindow::cameraLock = false;
	bool MainWindow::firstMouse = true;
	bool MainWindow::hideCursor = false;

	static void FrameBufferSizeCallback(GLFWwindow* window_p, int32 width_p, int32 height_p)
	{
		//glViewport(0, 0, width_p, height_p);
		//glViewport(width_p / 6, height_p / 3, width_p / 6 * 4, height_p / 3 * 2);
		/*int displayW, displayH;
		glfwGetFramebufferSize(window_p, &displayW, &displayH);
		glViewport(displayW / 6, displayH / 3, displayW / 6 * 4, displayH / 3 * 2);*/
		
		/*int32 displayW, displayH;
		glfwGetFramebufferSize(window_p, &displayW, &displayH);
		SetWindowSize(displayW, displayH);
		glViewport(displayW / 6, displayH / 3, displayW / 6 * 4, displayH / 3 * 2);*/
	}

	static void MouseMoveCallback(GLFWwindow* window_p, float64 xPos_p, float64 yPos_p)
	{
		if (!MainWindow::cameraLock)
		{
			float32 xpos = static_cast<float32>(xPos_p);
			float32 ypos = static_cast<float32>(yPos_p);
			if (MainWindow::firstMouse)
			{
				Mouse::GetInstance().xPos = xpos;
				Mouse::GetInstance().yPos = ypos;
				MainWindow::firstMouse = false;
			}

			Mouse::GetInstance().xOffset = xpos - Mouse::GetInstance().lastX;
			Mouse::GetInstance().yOffset = Mouse::GetInstance().lastY - ypos;

			Mouse::GetInstance().lastX = xpos;
			Mouse::GetInstance().lastY = ypos;

			if (Mouse::GetInstance().buttonRight)
			{
				MainWindow::cameraMapper [window_p]->ProcessMouseMovement(Mouse::GetInstance().xOffset,
																		  Mouse::GetInstance().yOffset);
			}
		}
	}

	static void MouseClickCallback(GLFWwindow* window_p, int32 button_p, int32 state_p, int32 mod_p)
	{
		if (button_p == GLFW_MOUSE_BUTTON_LEFT && state_p == GLFW_PRESS)
			Mouse::GetInstance().buttonLeft = true;
		if (button_p == GLFW_MOUSE_BUTTON_LEFT && state_p == GLFW_RELEASE)
			Mouse::GetInstance().buttonLeft = false;
		if (button_p == GLFW_MOUSE_BUTTON_RIGHT && state_p == GLFW_PRESS)
			Mouse::GetInstance().buttonRight = true;
		if (button_p == GLFW_MOUSE_BUTTON_RIGHT && state_p == GLFW_RELEASE)
			Mouse::GetInstance().buttonRight = false;

	}

	void MouseScrollCallback(GLFWwindow* window_p, float64 xOffset_p, float64 yOffset_p)
	{
		MainWindow::cameraMapper [window_p]->ProcessMouseScroll(static_cast<float32>(yOffset_p));
	}

	static void ErrorCallBack(int32 error_p, const char* description_p)
	{
		std::cout << "GLFW Error " << error_p << ": " << description_p << std::endl;
	}

	MainWindow::MainWindow(uint32 width_p, uint32 height_p, const char* windowID_p,
						   Camera* camera_p, RenderPipeline* renderPipeline_p) :
		width(width_p), height(height_p), windowID(windowID_p), camera(camera_p), renderPipeline(renderPipeline_p)
	{
		camera = camera_p;
		windowID = windowID_p;
		width = width_p; height = height_p;
		renderPipeline = renderPipeline_p;
		window = InitWindow();
		cameraMapper.insert({ window, camera });
	}

	MainWindow::~MainWindow()
	{
	}

	void MainWindow::WindowTerminate()
	{
		if (window != nullptr)
			glfwDestroyWindow(window);
		glfwTerminate();
	}

	uint32 MainWindow::GetWindowWidth()
	{
		return width;
	}

	uint32 MainWindow::GetWindowHeight()
	{
		return height;
	}

	void MainWindow::SetWindowSize(uint32 width_p, uint32 height_p)
	{
		width = width_p; height = height_p;
	}

	GLFWwindow* MainWindow::InitWindow()
	{
		if (!glfwInit())
			return nullptr;

		glfwSetErrorCallback(ErrorCallBack);

		// Decide GL+GLSL versions
	#if defined(IMGUI_IMPL_OPENGL_ES2)
		// GL ES 2.0 + GLSL 100
		const char* glsl_version = "#version 100";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	#elif defined(__APPLE__)
		// GL 3.2 + GLSL 150
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
	#else
		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	#endif

		GLFWwindow* window = glfwCreateWindow(width, height, windowID, nullptr, nullptr);
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return NULL;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
		glfwSetCursorPosCallback(window, MouseMoveCallback);
		glfwSetMouseButtonCallback(window, MouseClickCallback);
		glfwSetScrollCallback(window, MouseScrollCallback);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return NULL;
		}

		glEnable(GL_DEPTH_TEST);

		return window;
	}
}
