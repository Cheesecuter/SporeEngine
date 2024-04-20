#include <Spore.hpp>
#include <Mouse.hpp>
#include <Keyboard.hpp>
#include <AssetsManager.hpp>
#include <BasicModelsRegister.hpp>
#include <BasicShadersRegister.hpp>
#include <Serializer.hpp>
#include <Scene.hpp>
#include <PostProcess.hpp>
#include <PostProcesser.hpp>


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
		m_graphic_renderer->Init();
		m_audio_renderer->Init();
		Camera* editorCamera = m_graphic_renderer->GetCamera();
		RenderPipeline* renderPipeline = m_graphic_renderer->GetRenderPipeline();
		if (editorCamera != nullptr && renderPipeline != nullptr)
		{
			m_window = new MainWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Spore Engine", editorCamera, renderPipeline);
			m_ui = new UI(m_window);
		}
		Mouse::GetInstance().Update();
		Keyboard::GetInstance();
		AssetsManager::GetInstance();
		m_physicSystem = new PhysicSystem();
		m_audio_renderer->GetAudioSystem()->Init();
		m_physicSystem->Init();
		m_ui->Init();
		m_graphic_renderer->SetFlipVerticallyOnLoad(false);
		m_serializer = new Serializer();
	}

	void _Spore::PreProcessing()
	{
		m_graphic_renderer->GetRenderPipeline()->SetScenePos(m_window->m_width / 6, m_window->m_height / 3);
		m_graphic_renderer->GetRenderPipeline()->SetSceneSize(m_window->m_width / 6 * 4, m_window->m_height / 3 * 2);

		BasicModelsRegister basicModelsRegister;
		BasicShadersRegister basicShadersRegister;

		std::vector<Scene*> scenesFromJson;
		m_serializer->SetPhysicSystem(m_physicSystem);
		m_serializer->Deserialize("./Assets/Configs/config3.json");
		scenesFromJson = m_serializer->GetScenes();
		for (int i = 0; i < scenesFromJson.size(); i++)
		{
			m_window->m_render_pipeline->AddScene(scenesFromJson [i]);
		}

		m_window->m_render_pipeline->InitGrid();
		m_window->m_render_pipeline->InitSkyBox();


		Shader* postProcessDefaultShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/DefaultPostProcessFS.glsl");
		Shader* postProcessInversionShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/InversionPostProcessFS.glsl");
		Shader* postProcessGrayscaleShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/GrayscalePostProcessFS.glsl");
		Shader* postProcessSharpenShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/SharpenPostProcessFS.glsl");
		Shader* postProcessBlurShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/BlurPostProcessFS.glsl");
		Shader* postProcessEdgeDetectionShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/EdgeDetectionPostProcessFS.glsl");

		PostProcess* postProcessDefault = new PostProcess("Default", postProcessDefaultShader);
		m_window->m_render_pipeline->InitPostProcesser((uint32) m_window->m_render_pipeline->GetSceneSize().x, (uint32) m_window->m_render_pipeline->GetSceneSize().y, postProcessDefault);

		m_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessDefault);
		PostProcess* postProcessInversion = new PostProcess("Inversion", postProcessInversionShader);
		m_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessInversion);
		PostProcess* postProcessGrayscale = new PostProcess("Grayscale", postProcessGrayscaleShader);
		m_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessGrayscale);
		PostProcess* postProcessSharpen = new PostProcess("Sharpen", postProcessSharpenShader);
		m_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessSharpen);
		PostProcess* postProcessBlur = new PostProcess("Blur", postProcessBlurShader);
		m_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessBlur);
		PostProcess* postProcessEdgeDetection = new PostProcess("Edge Detection", postProcessEdgeDetectionShader);
		m_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessEdgeDetection);
	
		glfwPollEvents();
		vec4f backgroungColor = m_window->m_render_pipeline->GetBackgroundColor();
		glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

		while (!glfwWindowShouldClose(m_window->m_window))
		{
			currentFrame = static_cast<float32>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			m_ui->m_delta_time = deltaTime;

			uint32 windowWidth = m_window->GetWindowWidth();
			uint32 windowHeight = m_window->GetWindowHeight();

			vec4f backgroungColor = m_window->m_render_pipeline->GetBackgroundColor();
			glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_ui->NewFrame();

			m_ui->RenderPanels(m_window);

			Keyboard::GetInstance().processInput(m_window, *editorCamera, deltaTime);

			mat4f projection = glm::perspective(glm::radians(editorCamera->m_zoom),
												(float32) (windowWidth / windowHeight),
												0.1f, 10000.0f);
			mat4f view = editorCamera->GetViewMatrix();
			mat4f model = mat4f(1.0f);
			m_window->m_render_pipeline->PreRender();

			m_window->m_render_pipeline->SetScenePos(windowWidth / 6, windowHeight / 3);
			m_window->m_render_pipeline->SetSceneSize(windowWidth / 6 * 4, windowHeight / 3 * 2);

			if (m_window->m_render_pipeline->m_post_process_on)
			{
				m_window->m_render_pipeline->PostProcessRenderToFBO();
			}

			m_window->m_render_pipeline->Render(shaders, editorCamera,
												(uint32) windowWidth, (uint32) windowHeight,
												projection, view, model, deltaTime);
			m_window->m_render_pipeline->RenderSkyBox(editorCamera, projection, view);
			m_window->m_render_pipeline->RenderGrid(editorCamera, projection, view);

			if (m_window->m_render_pipeline->m_post_process_on)
			{
				m_window->m_render_pipeline->UpdateSceneFBO();
				m_window->m_render_pipeline->UpdateSceneRBO();
				m_window->m_render_pipeline->PostProcessFBO();
			}

			glViewport(windowWidth / 6, windowHeight / 3, windowWidth / 6 * 4, windowHeight / 3 * 2);
			glfwGetWindowSize(m_window->m_window, &displayW, &displayH);
			m_window->SetWindowSize(displayW, displayH);

			m_ui->Render();

			glfwSwapBuffers(m_window->m_window);
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