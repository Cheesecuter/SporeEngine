#include <Window.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>

namespace Spore
{
	std::map<GLFWwindow*, Camera*> MainWindow::m_camera_mapper;
	std::map<std::string, Scene*> MainWindow::m_scene_mapper;
	bool MainWindow::m_camera_lock = false;
	bool MainWindow::m_first_mouse = true;
	bool MainWindow::m_hide_cursor = false;


	static void FrameBufferSizeCallback(GLFWwindow* p_window, int32 p_width, int32 p_height);
	static void MouseMoveCallback(GLFWwindow* p_window, float64 p_x_pos, float64 p_y_pos);
	static void MouseClickCallback(GLFWwindow* p_window, int32 p_button, int32 p_state, int32 p_mod);
	void MouseScrollCallback(GLFWwindow* p_window, float64 p_x_offset, float64 p_y_offset);
	static void ErrorCallBack(int32 p_error, const char* p_description);

	MainWindow::MainWindow(uint32 p_width, uint32 p_height, const char* p_windowID,
						   Camera* p_camera, RenderPipeline* p_render_pipeline) :
		m_width(p_width), m_height(p_height), m_windowID(p_windowID), m_camera(p_camera), m_render_pipeline(p_render_pipeline)
	{
		m_camera = p_camera;
		m_windowID = p_windowID;
		m_width = p_width; m_height = p_height;
		m_render_pipeline = p_render_pipeline;
		m_window = InitWindow();
		m_camera_mapper.insert({ m_window, m_camera });
	}

	MainWindow::~MainWindow()
	{
	}

	void MainWindow::Terminate()
	{
		if (m_window != nullptr)
			glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	uint32 MainWindow::GetWindowWidth()
	{
		return m_width;
	}

	uint32 MainWindow::GetWindowHeight()
	{
		return m_height;
	}

	void MainWindow::SetWindowSize(uint32 p_width, uint32 p_height)
	{
		m_width = p_width; m_height = p_height;
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
			std::cout << "Failed to create GLFW window" << std::endl;
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
			std::cout << "Failed to initialize GLAD" << std::endl;
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

			if (Mouse::GetInstance().m_button_right)
			{
				MainWindow::m_camera_mapper [p_window]->ProcessMouseMovement(Mouse::GetInstance().m_x_offset,
																			 Mouse::GetInstance().m_y_offset);
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

	void MouseScrollCallback(GLFWwindow* p_window, float64 p_x_offset, float64 p_y_offset)
	{
		MainWindow::m_camera_mapper [p_window]->ProcessMouseScroll(static_cast<float32>(p_y_offset));
	}

	static void ErrorCallBack(int32 p_error, const char* p_description)
	{
		std::cout << "GLFW Error " << p_error << ": " << p_description << std::endl;
	}
}
