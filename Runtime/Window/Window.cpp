#include <Window.hpp>
#include <Keyboard.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>
#include <GraphicRenderer.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	std::map<std::string, Scene*> MainWindow::m_scene_mapper;
	Camera* MainWindow::m_camera = nullptr;
	bool MainWindow::m_camera_lock = false;
	bool MainWindow::m_first_mouse = true;
	bool MainWindow::m_hide_cursor = false;
	GraphicRenderer* MainWindow::m_graphic_renderer = nullptr;


	static void FrameBufferSizeCallback(GLFWwindow* p_window, int32 p_width, int32 p_height);
	static void MouseMoveCallback(GLFWwindow* p_window, float64 p_x_pos, float64 p_y_pos);
	static void MouseClickCallback(GLFWwindow* p_window, int32 p_button, int32 p_state, int32 p_mod);
	static void MouseScrollCallback(GLFWwindow* p_window, float64 p_x_offset, float64 p_y_offset);
	static void ErrorCallBack(int32 p_error, const char* p_description);

	MainWindow::MainWindow(uint32 p_width, uint32 p_height, const char* p_windowID,
						   Camera* p_camera, RenderPipeline* p_render_pipeline) :
		m_width(p_width), m_height(p_height), m_windowID(p_windowID)
	{
		m_windowID = p_windowID;
		m_width = p_width; m_height = p_height;
	}

	MainWindow::~MainWindow()
	{

	}

	void MainWindow::Init()
	{
		m_camera = m_graphic_renderer->GetCamera();
		m_window = InitWindow();
	}

	void MainWindow::Terminate()
	{
		if (m_window != nullptr)
			glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void MainWindow::SetWindowSize(uint32 p_width, uint32 p_height)
	{
		m_width = p_width; m_height = p_height;
	}

	uint32 MainWindow::GetWindowWidth()
	{
		return m_width;
	}

	uint32 MainWindow::GetWindowHeight()
	{
		return m_height;
	}

	void MainWindow::SetCamera(Camera* p_camera)
	{
		m_camera = p_camera;
		m_graphic_renderer->SetCamera(p_camera);
	}

	Camera* MainWindow::GetCamera()
	{
		return m_graphic_renderer->GetCamera();
	}

	bool MainWindow::TransformCamera(float32 p_delta_time)
	{
		if (Keyboard::GetInstance().GetKey(this) == KEY_ESC)
		{
			glfwSetWindowShouldClose(m_window, true);
			return true;
		}
		if (Keyboard::GetInstance().GetKey(this) == KEY_LEFT_CONTROL)
		{
			if (Keyboard::GetInstance().GetKey(this) == KEY_W)
			{
				m_camera->ProcessKeyboard(FORWARD, p_delta_time * 2);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_S)
			{
				m_camera->ProcessKeyboard(BACKWARD, p_delta_time * 2);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_A)
			{
				m_camera->ProcessKeyboard(LEFT, p_delta_time * 2);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_D)
			{
				m_camera->ProcessKeyboard(RIGHT, p_delta_time * 2);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_E)
			{
				m_camera->ProcessKeyboard(UP, p_delta_time * 2);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_Q)
			{
				m_camera->ProcessKeyboard(DOWN, p_delta_time * 2);
			}
		}
		else
		{
			if (Keyboard::GetInstance().GetKey(this) == KEY_W)
			{
				m_camera->ProcessKeyboard(FORWARD, p_delta_time);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_S)
			{
				m_camera->ProcessKeyboard(BACKWARD, p_delta_time);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_A)
			{
				m_camera->ProcessKeyboard(LEFT, p_delta_time);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_D)
			{
				m_camera->ProcessKeyboard(RIGHT, p_delta_time);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_E)
			{
				m_camera->ProcessKeyboard(UP, p_delta_time);
			}
			if (Keyboard::GetInstance().GetKey(this) == KEY_Q)
			{
				m_camera->ProcessKeyboard(DOWN, p_delta_time);
			}
		}
		return true;
	}

	void MainWindow::SetWindow(GLFWwindow* p_window)
	{
		m_window = p_window;
	}

	GLFWwindow* MainWindow::GetWindow()
	{
		return m_window;
	}

	void MainWindow::SetGraphicRenderer(GraphicRenderer* p_graphic_renderer)
	{
		m_graphic_renderer = p_graphic_renderer;
	}

	GraphicRenderer* MainWindow::GetGraphicRenderer()
	{
		return m_graphic_renderer;
	}

	RenderPipeline* MainWindow::GetRenderPipeline()
	{
		return m_graphic_renderer->GetRenderPipeline();
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

		GLFWwindow* m_window = glfwCreateWindow(m_width, m_height, m_windowID, nullptr, nullptr);
		if (m_window == nullptr)
		{
			ConsoleLogger::GetInstance().Logger()->error("MainWindow::InitWindow: Failed to create GLFW window");
			glfwTerminate();
			return NULL;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
		glfwSetCursorPosCallback(m_window, MouseMoveCallback);
		glfwSetMouseButtonCallback(m_window, MouseClickCallback);
		glfwSetScrollCallback(m_window, MouseScrollCallback);

		int32 width, height, nrComponents;
		unsigned char* data = stbi_load("./Assets/Utils/Icons/Spore_32.png", &width, &height, &nrComponents, 0);
		GLFWimage icon;
		icon.width = width;
		icon.height = height;
		icon.pixels = data;
		const GLFWimage& constIcon = icon;
		glfwSetWindowIcon(m_window, 1, &constIcon);

		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			ConsoleLogger::GetInstance().Logger()->error("MainWindow::InitWindow: Failed to initialize GLAD");
			return NULL;
		}

		glEnable(GL_DEPTH_TEST);

		return m_window;
	}

	static void FrameBufferSizeCallback(GLFWwindow* p_window, int32 p_width, int32 p_height)
	{
		//glViewport(0, 0, width_p, height_p);
	}

	static void MouseMoveCallback(GLFWwindow* p_window, float64 p_x_pos, float64 p_y_pos)
	{
		if (!MainWindow::m_camera_lock)
		{
			float32 xpos = static_cast<float32>(p_x_pos);
			float32 ypos = static_cast<float32>(p_y_pos);
			if (MainWindow::m_first_mouse)
			{
				Mouse::GetInstance().m_x_pos = xpos;
				Mouse::GetInstance().m_y_pos = ypos;
				MainWindow::m_first_mouse = false;
			}

			Mouse::GetInstance().m_x_offset = xpos - Mouse::GetInstance().m_last_x;
			Mouse::GetInstance().m_y_offset = Mouse::GetInstance().m_last_y - ypos;

			Mouse::GetInstance().m_last_x = xpos;
			Mouse::GetInstance().m_last_y = ypos;

			if (Mouse::GetInstance().m_button_right && g_tick_stop)
			{
				MainWindow::m_camera->ProcessMouseMovement(Mouse::GetInstance().m_x_offset,
														   Mouse::GetInstance().m_y_offset);
			}
			else if (g_tick_run)
			{
				if (glfwGetKey(p_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
				{
					glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
				else
				{
					glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					MainWindow::m_camera->ProcessMouseMovement(Mouse::GetInstance().m_x_offset,
															   Mouse::GetInstance().m_y_offset);
				}
			}
		}
	}

	static void MouseClickCallback(GLFWwindow* p_window, int32 p_button, int32 p_state, int32 p_mod)
	{
		if (p_button == GLFW_MOUSE_BUTTON_LEFT && p_state == GLFW_PRESS)
			Mouse::GetInstance().m_button_left = true;
		if (p_button == GLFW_MOUSE_BUTTON_LEFT && p_state == GLFW_RELEASE)
			Mouse::GetInstance().m_button_left = false;
		if (p_button == GLFW_MOUSE_BUTTON_RIGHT && p_state == GLFW_PRESS)
			Mouse::GetInstance().m_button_right = true;
		if (p_button == GLFW_MOUSE_BUTTON_RIGHT && p_state == GLFW_RELEASE)
			Mouse::GetInstance().m_button_right = false;

	}

	static void MouseScrollCallback(GLFWwindow* p_window, float64 p_x_offset, float64 p_y_offset)
	{
		vec2f pos = MainWindow::GetGraphicRenderer()->GetRenderPipeline()->GetScenePos();
		vec2f size = MainWindow::GetGraphicRenderer()->GetRenderPipeline()->GetSceneSize();

		float32 x1 = pos.x;
		float32 y1 = 0;
		float32 x2 = x1 + size.x;
		float32 y2 = size.y;

		float32 xPos = Mouse::GetInstance().m_last_x;
		float32 yPos = Mouse::GetInstance().m_last_y;

		if (xPos >= x1 && xPos <= x2 && yPos >= y1 && yPos <= y2)
		{
			MainWindow::m_camera->ProcessMouseScroll(static_cast<float32>(p_y_offset));
		}
	}

	static void ErrorCallBack(int32 p_error, const char* p_description)
	{
		ConsoleLogger::GetInstance().Logger()->error("MainWindow::ErrorCallBack: GLFW Error {}: {}", p_error, p_description);
	}
}
