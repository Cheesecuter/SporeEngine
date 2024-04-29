#include <Spore.hpp>
#include <GraphicRenderer.hpp>
#include <AudioRenderer.hpp>
#include <Window.hpp>
#include <UI.hpp>
#include <PhysicSystem.hpp>
#include <ScriptEngine.hpp>
#include <Mouse.hpp>
#include <Keyboard.hpp>
#include <AssetsManager.hpp>
#include <BasicModelsRegister.hpp>
#include <BasicShadersRegister.hpp>
#include <BasicTexturesRegister.hpp>
#include <Serializer.hpp>
#include <Scene.hpp>
#include <PostProcess.hpp>
#include <PostProcesser.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	_Spore::_Spore()
	{
		m_graphic_renderer = new GraphicRenderer();
		m_audio_renderer = new AudioRenderer();
	}

	_Spore::~_Spore()
	{
		delete m_audio_renderer;
		delete m_graphic_renderer;
	}

	void _Spore::Init()
	{
		spdlog::cfg::load_env_levels();
		m_graphic_renderer->Init();
		m_graphic_renderer->SetFlipVerticallyOnLoad(false);
		m_audio_renderer->Init();
		Camera* editorCamera = m_graphic_renderer->GetCamera();
		Camera* playerCamera = new Camera(0.0f, 1.0f, 0.0f);
		RenderPipeline* renderPipeline = m_graphic_renderer->GetRenderPipeline();
		if (editorCamera != nullptr && renderPipeline != nullptr)
		{
			m_window = new MainWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Spore Engine", editorCamera, renderPipeline);
			m_window->SetGraphicRenderer(m_graphic_renderer);
			m_window->Init();
			m_ui = new UI(m_window);
		}
		Mouse::GetInstance().Update();
		Keyboard::GetInstance().SetWindow(m_window);
		AssetsManager::GetInstance();
		BasicTexturesRegister basicTextureRegister;
		BasicModelsRegister basicModelsRegister;
		BasicShadersRegister basicShadersRegister;
		m_physicSystem = new PhysicSystem();
		m_audio_renderer->GetAudioSystem()->Init();
		m_physicSystem->Init();
		m_ui->Init();
		m_serializer = new Serializer();
		m_script_engine = new ScriptEngine();
		m_script_engine->Init();
	}

	void _Spore::PreProcessing()
	{
		m_graphic_renderer->GetRenderPipeline()->SetScenePos(m_window->GetWindowWidth() / 6, m_window->GetWindowHeight() / 3);
		m_graphic_renderer->GetRenderPipeline()->SetSceneSize(m_window->GetWindowWidth() / 6 * 4, m_window->GetWindowHeight() / 3 * 2);

		std::vector<Scene*> scenesFromJson;
		m_serializer->SetPhysicSystem(m_physicSystem);
		m_serializer->Deserialize("./Assets/Configs/config3.json");
		scenesFromJson = m_serializer->GetScenes();
		for (int i = 0; i < scenesFromJson.size(); i++)
		{
			m_window->GetRenderPipeline()->AddScene(scenesFromJson [i]);
		}

		m_window->GetRenderPipeline()->InitGrid();
		m_window->GetRenderPipeline()->InitSkyBox();


		Shader* postProcessDefaultShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/DefaultPostProcessFS.glsl");
		Shader* postProcessInversionShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/InversionPostProcessFS.glsl");
		Shader* postProcessGrayscaleShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/GrayscalePostProcessFS.glsl");
		Shader* postProcessSharpenShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/SharpenPostProcessFS.glsl");
		Shader* postProcessBlurShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/BlurPostProcessFS.glsl");
		//Shader* postProcessBlurShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/VoronoiNoiseFragment.glsl");
		//Shader* voronoiNoiseShader = new Shader("./Assets/Shaders/VoronoiNoiseVertex.glsl", "./Assets/Shaders/VoronoiNoiseFragment.glsl");
		Shader* postProcessEdgeDetectionShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/EdgeDetectionPostProcessFS.glsl");

		PostProcess* postProcessDefault = new PostProcess("Default", postProcessDefaultShader);
		m_window->GetRenderPipeline()->InitPostProcesser((uint32) m_window->GetRenderPipeline()->GetSceneSize().x, (uint32) m_window->GetRenderPipeline()->GetSceneSize().y, postProcessDefault);

		m_window->GetRenderPipeline()->GetPostProcesser()->AddPostProcess(postProcessDefault);
		PostProcess* postProcessInversion = new PostProcess("Inversion", postProcessInversionShader);
		m_window->GetRenderPipeline()->GetPostProcesser()->AddPostProcess(postProcessInversion);
		PostProcess* postProcessGrayscale = new PostProcess("Grayscale", postProcessGrayscaleShader);
		m_window->GetRenderPipeline()->GetPostProcesser()->AddPostProcess(postProcessGrayscale);
		PostProcess* postProcessSharpen = new PostProcess("Sharpen", postProcessSharpenShader);
		m_window->GetRenderPipeline()->GetPostProcesser()->AddPostProcess(postProcessSharpen);
		PostProcess* postProcessBlur = new PostProcess("Blur", postProcessBlurShader);
		m_window->GetRenderPipeline()->GetPostProcesser()->AddPostProcess(postProcessBlur);
		PostProcess* postProcessEdgeDetection = new PostProcess("Edge Detection", postProcessEdgeDetectionShader);
		m_window->GetRenderPipeline()->GetPostProcesser()->AddPostProcess(postProcessEdgeDetection);
	
		glfwPollEvents();
		vec4f backgroungColor = m_window->GetRenderPipeline()->GetBackgroundColor();
		glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	static void Hello(MonoString* name)
	{
		std::cout << "Hello, " << mono_string_to_utf8(name) << "!" << std::endl;
	}

	void _Spore::Runtime()
	{
		auto currentFrame = static_cast<float32>(glfwGetTime());
		float32 deltaTime = 0.0f;
		float32 lastFrame = 0.0f;
		int32 displayW, displayH;

		std::vector<Shader*> shaders;

		Camera* editorCamera = m_graphic_renderer->GetCamera();
		RenderPipeline* renderPipeline = m_graphic_renderer->GetRenderPipeline();

		MonoAssembly* appAssembly = m_script_engine->GetAppAssembly();
		appAssembly = m_script_engine->LoadAssembly("D:/SporeEngine/ScriptEngine/ScriptEngine/bin/Debug/net6.0/ScriptEngine.dll");
		if (!appAssembly)
		{
			ConsoleLogger::GetInstance().Logger()->error("Assembly Error");
		}
		else
		{
			ConsoleLogger::GetInstance().Logger()->info("Assembly Loaded");
		}

		MonoDomain* appDomain = m_script_engine->GetAppDomain();

		mono_add_internal_call("Spore.HelloClass::Hello", reinterpret_cast<void*>(&Hello));

		void* args [1];
		args [0] = mono_array_new(appDomain, mono_get_string_class(), 0);
		MonoClass* programClass = m_script_engine->GetClassInAssembly(appAssembly, "Spore", "MainClass");
		MonoMethod* mainMethod = mono_class_get_method_from_name(programClass, "Main", 1);
		MonoObject* result = mono_runtime_invoke(mainMethod, nullptr, args, nullptr);
		int resultCode = *static_cast<int*>(mono_object_unbox(result));

		while (!glfwWindowShouldClose(m_window->GetWindow()))
		{
			currentFrame = static_cast<float32>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			m_ui->m_delta_time = deltaTime;
			Camera* editorCamera = m_graphic_renderer->GetCamera();

			uint32 windowWidth = m_window->GetWindowWidth();
			uint32 windowHeight = m_window->GetWindowHeight();

			vec4f backgroungColor = m_window->GetRenderPipeline()->GetBackgroundColor();
			glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_ui->NewFrame();

			m_window->GetRenderPipeline()->SetScenePos(windowWidth / 6, windowHeight / 3);
			m_window->GetRenderPipeline()->SetSceneSize(windowWidth / 6 * 4, windowHeight / 3 * 2);

			m_ui->RenderPanels(m_window);

			if (g_tick_stop)
			{
				Keyboard::GetInstance().processInput(m_window, *editorCamera, deltaTime);
			}
			//m_window->TransformCamera(deltaTime);

			/*mat4f projection = glm::perspective(glm::radians(editorCamera->m_zoom),
												(float32) (windowWidth / windowHeight),
												0.1f, 10000.0f);*/
			mat4f projection = glm::perspective(glm::radians(editorCamera->m_zoom),
												(float32) (m_window->GetRenderPipeline()->GetSceneSize().x / m_window->GetRenderPipeline()->GetSceneSize().y),
												0.1f, 10000.0f);
			mat4f view = editorCamera->GetViewMatrix();
			mat4f model = mat4f(1.0f);

			m_window->GetRenderPipeline()->PreRender();


			if (m_window->GetRenderPipeline()->m_post_process_on)
			{
				m_window->GetRenderPipeline()->PostProcessRenderToFBO();
			}

			m_window->GetRenderPipeline()->Render(editorCamera,
												(uint32) windowWidth, (uint32) windowHeight, deltaTime);
			m_window->GetRenderPipeline()->RenderSkyBox(editorCamera, projection, view);
			m_window->GetRenderPipeline()->RenderGrid(editorCamera, projection, view);

			if (m_window->GetRenderPipeline()->m_post_process_on)
			{
				m_window->GetRenderPipeline()->UpdateSceneFBO();
				m_window->GetRenderPipeline()->UpdateSceneRBO();
				m_window->GetRenderPipeline()->PostProcessFBO();
			}

			glViewport(windowWidth / 6, windowHeight / 3, windowWidth / 6 * 4, windowHeight / 3 * 2);
			glfwGetWindowSize(m_window->GetWindow(), &displayW, &displayH);
			m_window->SetWindowSize(displayW, displayH);

			m_ui->Render();

			glfwSwapBuffers(m_window->GetWindow());
			glfwPollEvents();
		}
	}

	void _Spore::Terminate()
	{
		m_ui->Terminate();
		m_physicSystem->Terminate();
		m_audio_renderer->GetAudioSystem()->Terminate();
		m_window->Terminate();
		m_audio_renderer->Terminate();
		m_graphic_renderer->Terminate();
	}
}