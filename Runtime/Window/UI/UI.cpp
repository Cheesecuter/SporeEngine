#define GLFW_INCLUDE_NONE

#include <UI.hpp>
#include <AudioComponent.hpp>
#include <CameraComponent.hpp>
#include <LightComponent.hpp>
#include <ModelComponent.hpp>
#include <PhysicsComponent.hpp>
#include <ShaderComponent.hpp>
#include <TransformComponent.hpp>
#include <CameraComponent.hpp>
#include <CharacterControllerComponent.hpp>
#include <ConsoleLogger.hpp>

namespace fs = std::filesystem;
namespace Spore
{
	const char* glsl_version = "#version 130";

	UI::UI(MainWindow* p_window)
	{
		m_gizmos = new Gizmos();
		m_window = p_window;
		m_editor_camera = p_window->GetCamera();
		m_player_camera = new Camera(0.0f, 1.0f, 0.0f);

		ConsoleLogger::GetInstance().InitLogger();
		ConsoleLogger::GetInstance().Logger()->info("Console info");
	}

	UI::~UI()
	{

	}

	void UI::Init()
	{
		InitImGui(m_window);
		InitImages();
	}

	void UI::InitImGui(MainWindow* p_window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

		//ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(p_window->GetWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors [ImGuiCol_TitleBg] = ImVec4(0.289f, 0.289f, 0.289f, 1.0f);
		style.Colors [ImGuiCol_TitleBgActive] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_TitleBgCollapsed] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		//style.Colors [ImGuiCol_MenuBarBg] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_Button] = ImVec4(0.289f, 0.289f, 0.289f, 1.0f);
		style.Colors [ImGuiCol_ButtonActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);
		style.Colors [ImGuiCol_ButtonHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);
		//style.Colors [ImGuiCol_PopupBg] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		//style.Colors [ImGuiCol_ChildBg] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_ChildBg] = ImVec4(0.176f, 0.176f, 0.176f, 1.0f);
		style.Colors [ImGuiCol_Header] = ImVec4(0.251f, 0.251f, 0.251f, 1.0f);				//
		style.Colors [ImGuiCol_HeaderActive] = ImVec4(0.243f, 0.243f, 0.243f, 1.0f);
		style.Colors [ImGuiCol_HeaderHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);
		//style.Colors [ImGuiCol_FrameBg] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_FrameBg] = ImVec4(0.176f, 0.176f, 0.176f, 1.0f);
		style.Colors [ImGuiCol_FrameBgActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);
		style.Colors [ImGuiCol_FrameBgHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);
		style.Colors [ImGuiCol_Tab] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_TabActive] = ImVec4(0.243f, 0.243f, 0.243f, 1.0f);
		style.Colors [ImGuiCol_TabHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);
		style.Colors [ImGuiCol_SliderGrab] = ImVec4(0.289f, 0.289f, 0.289f, 1.0f);
		style.Colors [ImGuiCol_SliderGrabActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);
		style.Colors [ImGuiCol_WindowBg] = ImVec4(0.141f, 0.141f, 0.141f, 1.0f);


	#ifdef __EMSCRIPTEN__
		ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
	#endif
	}

	void UI::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UI::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UI::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UI::RenderPanels(MainWindow* p_window)
	{
		/*int32 displayW, displayH;
		glfwGetFramebufferSize(window_p->window, &displayW, &displayH);
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = displayW;
		io.DisplaySize.y = displayH;*/

		RenderMenuBar(p_window);
		RenderHierarchyPanel(p_window);
		if (m_show_scene_panel)
		{
			RenderScenePanel(p_window);
		}
		RenderGizmos(p_window);
		RenderInspectorPanel(p_window);
		RenderProjectPanel(p_window);
		RenderConsolePanel(p_window);

		ShowDemoWindow();
	}

	void UI::RenderMenuBar(MainWindow* p_window)
	{
		int32 width = p_window->GetWindowWidth();
		int32 height = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 2.0f);
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar;
		{
			ImGui::Begin("Menu Bar", &pOpen, windowFlags);
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("New Scene", NULL, false, true);
					ImGui::MenuItem("Open Scene", NULL, false, true);
					ImGui::MenuItem("Open Recent Scene", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Save", NULL, false, true);
					ImGui::MenuItem("Save As...", NULL, false, true);
					ImGui::MenuItem("Save As Scene Template...", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("New Project...", NULL, false, true);
					ImGui::MenuItem("Open Project...", NULL, false, true);
					ImGui::MenuItem("Save Project", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Build Settings...", NULL, false, true);
					ImGui::MenuItem("Build And Run", NULL, false, true);
					ImGui::Separator();
					if (ImGui::MenuItem("Exit"))
					{
						glfwSetWindowShouldClose(p_window->GetWindow(), true);
					}

					ImGui::SeparatorText("============");
					ImGui::SeparatorText("============");
					if (ImGui::MenuItem("Import Model"))
					{
						m_import_assets_path = Files::GetInstance().GetAssetsPath() / "Models";
						FileExplorer::GetInstance().Explorer(p_window, &m_import_assets_path, AssetsType::MODEL);
						static char model_path [512];
						strcpy_s(model_path, m_import_assets_path.string().c_str());
						std::string path_s = model_path;
						Model* new_model = new Model(std::filesystem::path(path_s).string().c_str());
					}
					if (ImGui::MenuItem("Import Shader"))
					{
						m_import_assets_path = Files::GetInstance().GetAssetsPath() / "Shaders";
						FileExplorer::GetInstance().Explorer(p_window, &m_import_assets_path, AssetsType::SHADER);
						static char shader_path [512];
						strcpy_s(shader_path, m_import_assets_path.string().c_str());
						std::string path_s = shader_path;
						Model* new_model = new Model(std::filesystem::path(path_s).string().c_str());
					}
					if (ImGui::MenuItem("Import Texture"))
					{
						m_import_assets_path = Files::GetInstance().GetAssetsPath() / "Textures";
						FileExplorer::GetInstance().Explorer(p_window, &m_import_assets_path, AssetsType::TEXTURE);
						static char texture_path [512];
						strcpy_s(texture_path, m_import_assets_path.string().c_str());
						std::string path_s = texture_path;
						Texture* new_texture = new Texture(std::filesystem::path(path_s).string().c_str());
					}
					if (ImGui::MenuItem("Import Audio"))
					{
						m_import_assets_path = Files::GetInstance().GetAssetsPath() / "Audios";
						FileExplorer::GetInstance().Explorer(p_window, &m_import_assets_path, AssetsType::AUDIO);
						static char audio_path [512];
						strcpy_s(audio_path, m_import_assets_path.string().c_str());
						std::string path_s = audio_path;
						Audio* new_audio = new Audio(std::filesystem::path(path_s).string().c_str());
					}
					ImGui::SeparatorText("General Setting");
					ImGui::Checkbox("Show Skybox", &p_window->GetRenderPipeline()->m_skybox_on);
					ImGui::Checkbox("Show Grid", &p_window->GetRenderPipeline()->m_grid_on);
					ImGui::Separator();
					ImGui::Checkbox("Gamma Correction", &p_window->GetRenderPipeline()->m_gamma_correction_on);
					ImGui::Checkbox("Shadow Mapping", &p_window->GetRenderPipeline()->m_shadow_map_on);
					ImGui::Checkbox("Post Process", &p_window->GetRenderPipeline()->m_post_process_on);
					ImGui::Checkbox("Scene Panel", &m_show_scene_panel);
					ImGui::Separator();
					ImGui::SliderFloat("Camera Speed", &p_window->GetCamera()->m_movement_speed, 0.0f, 50.0f);
					static int32 windowSizeIndex = -1;
					ImGui::Checkbox("Console", &m_show_console);
					ImGui::Checkbox("Demo Window", &m_show_demo_window);
					ImGui::SeparatorText("============");
					ImGui::SeparatorText("============");

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Edit"))
				{
					ImGui::MenuItem("Undo Clear Selection", NULL, false, true);
					ImGui::MenuItem("Redo", NULL, false, true);
					ImGui::MenuItem("Undo History", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Select All", NULL, false, true);
					ImGui::MenuItem("Deselect All", NULL, false, true);
					ImGui::MenuItem("Select Children", NULL, false, true);
					ImGui::MenuItem("Select Prefab Root", NULL, false, true);
					ImGui::MenuItem("Invert Selection", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Cut", NULL, false, true);
					ImGui::MenuItem("Copy", NULL, false, true);
					ImGui::MenuItem("Paste", NULL, false, true);
					ImGui::MenuItem("Paste As Child", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Duplicate", NULL, false, true);
					ImGui::MenuItem("Rename", NULL, false, true);
					ImGui::MenuItem("Delete", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Frame Selected", NULL, false, true);
					ImGui::MenuItem("Lock View to Selected", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Find", NULL, false, true);
					ImGui::MenuItem("Search All...", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Play", NULL, false, true);
					ImGui::MenuItem("Pause", NULL, false, true);
					ImGui::MenuItem("Step", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Sign in...", NULL, false, true);
					ImGui::MenuItem("Sign out", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Selection", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Project Settings...", NULL, false, true);
					ImGui::MenuItem("Preferences...", NULL, false, true);
					ImGui::MenuItem("Shortcuts...", NULL, false, true);
					ImGui::MenuItem("Clear All PlayerPrefs", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Graphics Tier", NULL, false, true);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Assets"))
				{
					ImGui::MenuItem("Create", NULL, false, true);
					ImGui::MenuItem("Show in Explorer", NULL, false, true);
					ImGui::MenuItem("Open", NULL, false, true);
					ImGui::MenuItem("Delete", NULL, false, true);
					ImGui::MenuItem("Rename", NULL, false, true);
					ImGui::MenuItem("Copy Path", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Open Scene Additive", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("View in Package Manager", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Import New Asset...", NULL, false, true);
					ImGui::MenuItem("Import Package", NULL, false, true);
					ImGui::MenuItem("Export Package...", NULL, false, true);
					ImGui::MenuItem("Find References In Scene", NULL, false, true);
					ImGui::MenuItem("Select Dependencies", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Refresh", NULL, false, true);
					ImGui::MenuItem("Reimport", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Reimport All", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Extract From Prefab", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Update UXML Schema", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Open C# Project", NULL, false, true);
					ImGui::MenuItem("View in Import Activity Window", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Properties...", NULL, false, true);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Object"))
				{
					ImGui::MenuItem("Create Empty", NULL, false, true);
					ImGui::MenuItem("Create Empty Child", NULL, false, true);
					ImGui::MenuItem("Create Empty Parent", NULL, false, true);
					ImGui::MenuItem("3D Object", NULL, false, true);
					ImGui::MenuItem("Effects", NULL, false, true);
					ImGui::MenuItem("Light", NULL, false, true);
					ImGui::MenuItem("Audio", NULL, false, true);
					ImGui::MenuItem("Video", NULL, false, true);
					ImGui::MenuItem("UI", NULL, false, true);
					ImGui::MenuItem("UI Tookit", NULL, false, true);
					ImGui::MenuItem("Camera", NULL, false, true);
					ImGui::MenuItem("Visual Scripting Scene Variables", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Center On Children", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Make Parent", NULL, false, true);
					ImGui::MenuItem("Clear Parent", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Set as first sibling", NULL, false, true);
					ImGui::MenuItem("Set as last sibling", NULL, false, true);
					ImGui::MenuItem("Move To View", NULL, false, true);
					ImGui::MenuItem("Align With View", NULL, false, true);
					ImGui::MenuItem("Align View to Selected", NULL, false, true);
					ImGui::MenuItem("Toggle Active State", NULL, false, true);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Component"))
				{
					ImGui::MenuItem("Add...", NULL, false, true);
					ImGui::MenuItem("Mesh", NULL, false, true);
					ImGui::MenuItem("Effects", NULL, false, true);
					ImGui::MenuItem("Physics", NULL, false, true);
					ImGui::MenuItem("Physics 2D", NULL, false, true);
					ImGui::MenuItem("Navigation", NULL, false, true);
					ImGui::MenuItem("Audio", NULL, false, true);
					ImGui::MenuItem("Video", NULL, false, true);
					ImGui::MenuItem("Rendering", NULL, false, true);
					ImGui::MenuItem("Tilemap", NULL, false, true);
					ImGui::MenuItem("Layout", NULL, false, true);
					ImGui::MenuItem("Playables", NULL, false, true);
					ImGui::MenuItem("Miscellaneous", NULL, false, true);
					ImGui::MenuItem("Scripts", NULL, false, true);
					ImGui::MenuItem("UI", NULL, false, true);
					ImGui::MenuItem("Visual Scripting", NULL, false, true);
					ImGui::MenuItem("Event", NULL, false, true);
					ImGui::MenuItem("UI Tookit", NULL, false, true);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Windows"))
				{
					ImGui::MenuItem("Panels", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Next Window", NULL, false, true);
					ImGui::MenuItem("Previous Window", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Layouts", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Search", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Collaborate", NULL, false, true);
					ImGui::MenuItem("Plastic SCM", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Asset Store", NULL, false, true);
					ImGui::MenuItem("Package Manager", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Asset Management", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Text", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("TextMeshPro", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("General", NULL, false, true);
					ImGui::MenuItem("Rendering", NULL, false, true);
					ImGui::MenuItem("Animation", NULL, false, true);
					ImGui::MenuItem("Audio", NULL, false, true);
					ImGui::MenuItem("Sequencing", NULL, false, true);
					ImGui::MenuItem("Analysis", NULL, false, true);
					ImGui::MenuItem("AI", NULL, false, true);
					ImGui::MenuItem("UI Tookit", NULL, false, true);
					ImGui::MenuItem("Visual Scripting", NULL, false, true);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Help"))
				{
					ImGui::MenuItem("About", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Check for Updates", NULL, false, true);
					ImGui::MenuItem("Download Beta...", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Manage License", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Release Notes", NULL, false, true);
					ImGui::MenuItem("Software Licenses", NULL, false, true);
					ImGui::MenuItem("Report a Bug...", NULL, false, true);
					ImGui::Separator();
					ImGui::MenuItem("Reset Packages to defaults", NULL, false, true);
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}
	}

	void UI::RenderHierarchyPanel(MainWindow* p_window)
	{
		int32 width = p_window->GetWindowWidth() / 6;
		int32 height = p_window->GetWindowHeight() / 3 * 2;
		int32 height1 = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGui::SetNextWindowPos(ImVec2(0.0f, (float32) height1), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) (height - height1)), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Hierarchy", &pOpen, windowFlags);
			std::map<std::string, Scene*> sceneMapper = p_window->GetRenderPipeline()->m_scene_mapper;
			std::map<std::string, Object*> objectMapper;
			std::map<std::string, std::map<std::string, Object*>> sceneObjectMapper;
			for (std::map<std::string, Scene*>::iterator it_scene = sceneMapper.begin(); it_scene != sceneMapper.end(); it_scene++)
			{
				objectMapper = it_scene->second->m_object_mapper;
				sceneObjectMapper.insert(std::make_pair(it_scene->first, objectMapper));
			}
			if (m_selected_scene_identifier != "")
			{
				m_selected_scene = sceneMapper.find(m_selected_scene_identifier)->second;
				if (m_selected_object_identifier != "")
				{
					m_selected_object = m_selected_scene->m_object_mapper.find(m_selected_object_identifier)->second;
					m_selected_object->m_selected = true;
				}
			}
			m_selected_scene = p_window->GetRenderPipeline()->m_scene_mapper.find("scene_1")->second;
			for (std::map<std::string, Scene*>::iterator it_scene = sceneMapper.begin(); it_scene != sceneMapper.end(); it_scene++)
			{
				{
					std::string childFrameIdentifier = "##Hierarchy::Scene::" + it_scene->second->m_identifier;
					int32 collapsingHeaderLength = (int32) it_scene->second->m_object_mapper.size() + 1;
					ImGui::BeginChild(childFrameIdentifier.c_str(), ImVec2((float32) (width - 4), (float32) (collapsingHeaderLength * height1)));

					//ImGui::SetItemTooltip(it_scene->second->m_identifier.c_str());
					if (ImGui::CollapsingHeader(it_scene->second->m_identifier.c_str(), true))
					{
						if (ImGui::BeginPopupContextItem())
						{
							if (ImGui::BeginMenu("Add Object"))
							{
								if (ImGui::BeginMenu("3D Object"))
								{
									if (ImGui::MenuItem("Cube", NULL, false, true))
									{
										std::string name = "cube";
										ModelObject* object = new ModelObject("obj_" + std::to_string(it_scene->second->m_object_index++) + "_" + name);
										object->SetModelType(ModelType::CUBE);
										object->AddModel(AssetsManager::GetInstance().m_model_mapper ["cube.obj"]);
										it_scene->second->AddObject(object);
										object->AddObserver(it_scene->second);
									}
									if (ImGui::MenuItem("Sphere", NULL, false, true))
									{
										std::string name = "sphere";
										ModelObject* object = new ModelObject("obj_" + std::to_string(it_scene->second->m_object_index++) + "_" + name);
										object->SetModelType(ModelType::SPHERE);
										object->AddModel(AssetsManager::GetInstance().m_model_mapper ["sphere.obj"]);
										it_scene->second->AddObject(object);
										object->AddObserver(it_scene->second);
									}
									if (ImGui::MenuItem("Capsule", NULL, false, true))
									{
										std::string name = "capsule";
										ModelObject* object = new ModelObject("obj_" + std::to_string(it_scene->second->m_object_index++) + "_" + name);
										object->SetModelType(ModelType::CAPSULE);
										object->AddModel(AssetsManager::GetInstance().m_model_mapper ["capsule.obj"]);
										it_scene->second->AddObject(object);
										object->AddObserver(it_scene->second);
									}
									if (ImGui::MenuItem("Cylinder", NULL, false, true))
									{
										std::string name = "cylinder";
										ModelObject* object = new ModelObject("obj_" + std::to_string(it_scene->second->m_object_index++) + "_" + name);
										object->SetModelType(ModelType::CYLINDER);
										object->AddModel(AssetsManager::GetInstance().m_model_mapper ["cylinder.obj"]);
										it_scene->second->AddObject(object);
										object->AddObserver(it_scene->second);
									}
									if (ImGui::MenuItem("Plane", NULL, false, true))
									{
										std::string name = "plane";
										ModelObject* object = new ModelObject("obj_" + std::to_string(it_scene->second->m_object_index++) + "_" + name);
										object->SetModelType(ModelType::PLANE);
										object->AddModel(AssetsManager::GetInstance().m_model_mapper ["plane.obj"]);
										it_scene->second->AddObject(object);
										object->AddObserver(it_scene->second);
									}
									if (ImGui::MenuItem("Quad", NULL, false, true))
									{
										std::string name = "quad";
										ModelObject* object = new ModelObject("obj_" + std::to_string(it_scene->second->m_object_index++) + "_" + name);
										object->SetModelType(ModelType::QUAD);
										object->AddModel(AssetsManager::GetInstance().m_model_mapper ["plane.obj"]);
										//object->AddModel(AssetsManager::GetInstance().m_model_mapper ["quad.fbx"]);
										it_scene->second->AddObject(object);
										object->AddObserver(it_scene->second);
									}
									if (ImGui::MenuItem("Model", NULL, false, true))
									{
										std::string name = "model";
										ModelObject* object = new ModelObject("obj_" + std::to_string(it_scene->second->m_object_index++) + "_" + name);
										//object->AddModel(modelMapper [name]);
										it_scene->second->AddObject(object);
										//modelMapper [name]->AddObserver(object);
										object->AddObserver(it_scene->second);
									}
									ImGui::EndMenu();
								}
								if (ImGui::BeginMenu("Light"))
								{
									ImGui::MenuItem("Directional Light", NULL, false, true);
									ImGui::MenuItem("Point Light", NULL, false, true);
									ImGui::MenuItem("Spotlight", NULL, false, true);
									ImGui::MenuItem("Area Light", NULL, false, true);
									ImGui::EndMenu();
								}
								ImGui::MenuItem("Camera", NULL, false, true);
								ImGui::EndMenu();
							}
							ImGui::EndPopup();
						}
						objectMapper = it_scene->second->m_object_mapper;
						for (std::map<std::string, Object*>::iterator it_object = objectMapper.begin(); it_object != objectMapper.end(); it_object++)
						{
							if (ImGui::Selectable(it_object->second->m_identifier.c_str(), m_selected_object_identifier == it_object->second->m_identifier))
							{
								/*if (ImGui::IsItemClicked())
								{
									selectedSceneIdentifier = it_scene->second->identifier;
									std::cout << selectedSceneIdentifier << std::endl;
								}*/
								m_selected_object_identifier = it_object->second->m_identifier;
								m_selected_object = it_scene->second->m_object_mapper.find(m_selected_object_identifier)->second;
								m_selected_object->m_selected = true;
							}
							if (m_selected_object != nullptr)
							{
								if (m_selected_object->HasComponent("Camera"))
								{
									CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(m_selected_object->GetComponent("Camera"));
									//cameraComponent->SetCamera(m_player_camera);
									m_player_camera = cameraComponent->GetCamera();
								}
							}
							if (ImGui::BeginPopupContextItem())
							{
								m_selected_object_identifier = it_object->second->m_identifier;
								ImGui::Text("%s", m_selected_object_identifier.c_str());
								ImGui::Separator();
								ImGui::MenuItem("Rename", NULL, false, true);
								ImGui::MenuItem("Duplicate", NULL, false, true);
								if (ImGui::MenuItem("Delete", NULL, false, true))
								{
									std::string name = m_selected_object_identifier;
									std::string subName = "";
									uint64 startPos = name.find("_");
									if (startPos != std::string::npos)
									{
										uint64 endPos = name.find("_", startPos + 1);
										if (endPos != std::string::npos)
										{
											subName = name.substr(endPos + 1);
										}
									}
									AssetsManager::GetInstance().m_model_counter [subName]--;
									//scene->objectMapper.erase(name);
									objectMapper.erase(name);
									it_scene->second->m_object_mapper.erase(name);
									it_object = objectMapper.begin();
									m_selected_object_identifier = "";
									if (it_object == objectMapper.end())
									{
										ImGui::EndPopup();
										break;
									}
								}
								ImGui::Separator();
								if (ImGui::MenuItem("Close", NULL, false, true))
									ImGui::CloseCurrentPopup();
								ImGui::EndPopup();
							}
							ImGui::SetItemTooltip(it_object->second->m_identifier.c_str());
						}
					}

					ImGui::EndChild();
				}
				
			}
			ImGui::End();
		}
	}

	void UI::RenderScenePanel(MainWindow* p_window)
	{
		int32 width = p_window->GetWindowWidth() / 6 * 4;
		int32 height = p_window->GetWindowHeight() / 3 * 2;
		int32 height1 = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGui::SetNextWindowPos(ImVec2((float32) (p_window->GetWindowWidth() - p_window->GetWindowWidth() / 6 * 5), (float32) height1), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) (height - height1)), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Scene", &pOpen, windowFlags);

			ImVec2 size = ImGui::GetContentRegionAvail();

			ImGuizmo::SetDrawlist();
			RenderGizmos(p_window);
			//p_window->m_render_pipeline->RenderSceneFramebufferEnd();
			//uint32 framebufferTexture = p_window->m_render_pipeline->GetSceneTexture();
			uint32 framebufferTexture = p_window->GetRenderPipeline()->GetPostProcesser()->GetFrameBufferTexture();
			ImGui::Image((void*) (intptr_t) framebufferTexture, size, ImVec2(0, 1), ImVec2(1, 0));

			ImGui::End();
		}
	}

	void UI::RenderInspectorPanel(MainWindow* p_window)
	{
		int32 width = p_window->GetWindowWidth() / 6;
		int32 height = p_window->GetWindowHeight() / 3 * 2;
		int32 height1 = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGui::SetNextWindowPos(ImVec2((float32) (p_window->GetWindowWidth() - width), (float32) height1), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) (height - height1)), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Inspector", &pOpen, windowFlags);

			if (m_selected_object != nullptr)
			{
				if (ImGui::CollapsingHeader(m_selected_object->m_identifier.c_str(), true))
				{
					ImGui::Text("Type: %s", m_selected_object->m_type.c_str());
					ImGui::Separator();
					if (m_selected_object->m_type == "Model")
					{
						ModelObject* modelObject = dynamic_cast<ModelObject*>(m_selected_object);
						ImGui::Text("Models");
						for (std::pair<std::string, Model*> it_model : modelObject->m_model_mapper)
						{
							ImGui::Text(it_model.second->m_identifier.c_str());
							ImGui::Separator();
						}
					}
					const char* layers [] = {
						"Default",
						"TransparentFX",
						"UI",
						"PostProcessing",
						"Terrain",
						"Background"
					};
					static int currentLayer = 0;
					ImGui::Text("Layer");
					if (ImGui::BeginCombo("##Layer", layers [currentLayer]))
					{
						for (uint32 i = 0; i < IM_ARRAYSIZE(layers); i++)
						{
							const bool isSelected = (currentLayer == i);
							if (ImGui::Selectable(layers [i], isSelected))
							{
								currentLayer = i;
							}
							if (isSelected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
					m_post_process_mapper = *p_window->GetRenderPipeline()->GetPostProcesser()->GetPostProcesses();
					std::vector<std::string> postProcesses;
					for (const std::pair<std::string, PostProcess*> it_postProcess : m_post_process_mapper)
					{
						postProcesses.push_back(it_postProcess.first);
					}
					static int currentPostProcess = 0;
					ImGui::Text("PostProcessing");
					if (ImGui::BeginCombo("##PostProcessing", postProcesses [currentPostProcess].c_str()))
					{
						for (uint32 i = 0; i < postProcesses.size(); i++)
						{
							const bool isSelected = (currentPostProcess == i);
							if (ImGui::Selectable(postProcesses [i].c_str(), isSelected))
							{
								currentPostProcess = i;
								p_window->GetRenderPipeline()->m_post_process = postProcesses [currentPostProcess];
								p_window->GetRenderPipeline()->GetPostProcesser()->SetPostProcess(postProcesses [currentPostProcess]);
							}
							if (isSelected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
				}
				std::unordered_map<std::string, Component*> components = m_selected_object->GetComponents();
				for (std::pair<std::string, Component*> it_component : components)
				{
					std::string componentName = it_component.second->GetName();
					it_component.second->InspectorPanel();
				}
				if (ImGui::Button("Add Component"))
				{
					m_show_adding_component_panel = true;
				}
			}

			if (m_show_adding_component_panel)
			{
				RenderAddingComponentsPanel(p_window);
			}

			ImGui::End();
		}
	}

	void UI::RenderProjectPanel(MainWindow* p_window)
	{
		int32 width = p_window->GetWindowWidth() / 10 * 6;
		int32 height = p_window->GetWindowHeight() / 3;
		int32 height1 = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGui::SetNextWindowPos(ImVec2(0.0f, (float32) (p_window->GetWindowHeight() - height)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Project", &pOpen, windowFlags);
			std::vector<std::string> shaderIdentifiers;
			std::vector<std::string> textureIdentifiers;
			std::vector<std::string> modelIdentifiers;
			std::vector<std::string> audioIdentifiers;
			std::map<std::string, Shader*> shaderMapper = AssetsManager::GetInstance().m_shader_mapper;
			for (std::map<std::string, Shader*>::iterator it = shaderMapper.begin(); it != shaderMapper.end(); it++)
			{
				shaderIdentifiers.push_back(it->first);
			}
			std::map<std::string, Texture*> textureMapper = AssetsManager::GetInstance().m_texture_mapper;
			for (std::map<std::string, Texture*>::iterator it = textureMapper.begin(); it != textureMapper.end(); it++)
			{
				textureIdentifiers.push_back(it->first);
			}
			std::map<std::string, Model*> modelMapper = AssetsManager::GetInstance().m_model_mapper;
			for (std::map<std::string, Model*>::iterator it = modelMapper.begin(); it != modelMapper.end(); it++)
			{
				modelIdentifiers.push_back(it->first);
			}
			std::map<std::string, Audio*> audioMapper = AssetsManager::GetInstance().m_audio_mapper;
			for (std::map<std::string, Audio*>::iterator it = audioMapper.begin(); it != audioMapper.end(); it++)
			{
				audioIdentifiers.push_back(it->first);
			}
			bool modelDetailsPanel = false;
			bool shaderDetailsPanel	= false;
			bool textureDetailsPanel = false;
			bool audioDetailsPanel = false;
			{
				ImGui::BeginChild("Assets Folders", ImVec2((float32) (width / 5 * 2), (float32) height - 35));
				ImGui::Image((ImTextureID) (intptr_t) m_image_folder->m_ID, ImVec2((float32) height1, (float32) height1));
				ImGui::SameLine();
				if (ImGui::CollapsingHeader("Assets", true))
				{
					ImGui::Image((ImTextureID) (intptr_t) m_image_folder_close->m_ID, ImVec2((float32) height1, (float32) height1));
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Models", true))
					{
						modelDetailsPanel = true;
						shaderDetailsPanel = false;
						textureDetailsPanel = false;
						audioDetailsPanel = false;
						static int32 selected_model = -1;
						for (uint32 n = 0; n < modelIdentifiers.size(); n++)
						{
							ImGui::Image((ImTextureID) (intptr_t) m_image_empty_file->m_ID, ImVec2((float32) height1, (float32) height1));
							ImGui::SameLine();
							if (ImGui::Selectable(modelIdentifiers [n].c_str(), selected_model == n))
							{
								selected_model = n;
							}
							if (ImGui::BeginDragDropSource())
							{
								selected_model = n;
								const char* identifier = modelIdentifiers [n].c_str();
								ImGui::PushID(std::string("Project::Assets::Models::" + modelIdentifiers [n]).c_str());
								ImGui::SetDragDropPayload("AssetModelDragDrop", identifier, strlen(identifier) + 1);
								ImGui::PopID();
								ImGui::Text("%s", identifier);
								ImGui::EndDragDropSource();
							}
							if (ImGui::BeginPopupContextItem())
							{
								selected_model = n;
								ImGui::Text("%s", modelIdentifiers [n].c_str());
								if (ImGui::Button("Create Object"))
								{
									std::string name = modelIdentifiers [n];
									Scene* scene = p_window->GetRenderPipeline()->m_scene_mapper.find("scene_1")->second;
									//std::shared_ptr<Object> object = std::make_shared<Object>("obj_" + std::to_string(modelCount) + "_" + modelMapper [name]->identifier);
									//std::shared_ptr<ModelObject> object = std::make_shared<ModelObject>("obj_" + std::to_string(modelCount) + "_" + modelMapper [name]->identifier);
									ModelObject* object = new ModelObject("obj_" + std::to_string(scene->m_object_index++) + "_" + modelMapper [name]->m_identifier);
									object->AddModel(modelMapper [name]);
									object->SetModelType(ModelType::QUAD);
									scene->AddObject(object);
									//modelMapper [name]->AddObserver(object);
									//object->AddObserver(scene);
									ImGui::CloseCurrentPopup();
								}
								if (ImGui::Button("Remove"))
								{
									selected_model = -1;
									m_selected_object_identifier = "";
									m_selected_object = nullptr;
									std::string name = modelIdentifiers [n];
									Model* modelTemp = AssetsManager::GetInstance().m_model_mapper [name];
									delete modelTemp;
									AssetsManager::GetInstance().m_model_mapper.erase(name);
								}
								if (ImGui::Button("Close"))
									ImGui::CloseCurrentPopup();
								ImGui::EndPopup();
							}
						}
					}
					ImGui::Image((ImTextureID) (intptr_t) m_image_folder_close->m_ID, ImVec2((float32) height1, (float32) height1));
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Shaders", true))
					{
						modelDetailsPanel = false;
						shaderDetailsPanel = true;
						textureDetailsPanel = false;
						audioDetailsPanel = false;
						static int32 selected_shader = -1;
						for (uint32 n = 0; n < shaderIdentifiers.size(); n++)
						{
							ImGui::Image((ImTextureID) (intptr_t) m_image_empty_file->m_ID, ImVec2((float32) height1, (float32) height1));
							ImGui::SameLine();
							if (ImGui::Selectable(shaderIdentifiers [n].c_str(), selected_shader == n))
							{
								selected_shader = n;
							}
							if (ImGui::BeginDragDropSource())
							{
								selected_shader = n;
								const char* identifier = shaderIdentifiers [n].c_str();
								ImGui::PushID(std::string("Project::Assets::Shaders::" + shaderIdentifiers[n]).c_str());
								ImGui::SetDragDropPayload("AssetShaderDragDrop", identifier, strlen(identifier) + 1);
								ImGui::PopID();
								ImGui::Text("%s", identifier);
								ImGui::EndDragDropSource();
							}
							if (ImGui::BeginPopupContextItem())
							{
								selected_shader = n;
								ImGui::Text("%s", shaderIdentifiers [n].c_str());
								if (ImGui::Button("Remove"))
								{
									Shader* tmp = AssetsManager::GetInstance().m_shader_mapper [shaderIdentifiers [n]];
									/*if (!tmp->IsEditor())
									{
										selected_shader = -1;
										delete tmp;
									}
									else
									{
										RendererConsole::GetInstance()->AddError("[error] Editor Shader can not be removed!");
									}*/
								}
								if (ImGui::Button("Close"))
									ImGui::CloseCurrentPopup();
								ImGui::EndPopup();
							}
						}
					}
					ImGui::Image((ImTextureID) (intptr_t) m_image_folder_close->m_ID, ImVec2((float32) height1, (float32) height1));
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Textures", true))
					{
						modelDetailsPanel = false;
						shaderDetailsPanel = false;
						textureDetailsPanel = true;
						audioDetailsPanel = false;
						static int32 selected_tex = -1;
						{
							for (uint32 n = 0; n < textureIdentifiers.size(); n++)
							{
								ImGui::Image((ImTextureID) (intptr_t) m_image_empty_file->m_ID, ImVec2((float32) height1, (float32) height1));
								ImGui::SameLine();
								if (ImGui::Selectable(textureIdentifiers [n].c_str(), selected_tex == n))
									selected_tex = n;
								if (ImGui::BeginPopupContextItem())
								{
									selected_tex = n;
									ImGui::Text("%s", textureIdentifiers [n].c_str());
									if (ImGui::Button("Remove"))
									{
										Texture* tmp = AssetsManager::GetInstance().m_texture_mapper [textureIdentifiers [n]];
										/*if (!tmp->is_editor)
										{
											selected_tex = -1;
											delete tmp;
										}
										else
										{
											RendererConsole::GetInstance()->AddError("[error] Editor Texture can not be deleted!");
										}*/
									}
									if (ImGui::Button("Close"))
										ImGui::CloseCurrentPopup();
									ImGui::EndPopup();
								}
							}
						}
					}
					ImGui::Image((ImTextureID) (intptr_t) m_image_folder_close->m_ID, ImVec2((float32) height1, (float32) height1));
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Audios", true))
					{
						modelDetailsPanel = false;
						shaderDetailsPanel = false;
						textureDetailsPanel = false;
						audioDetailsPanel = true;
						static int32 selected_audio = -1;
						for (uint32 n = 0; n < audioIdentifiers.size(); n++)
						{
							ImGui::Image((ImTextureID) (intptr_t) m_image_empty_file->m_ID, ImVec2((float32) height1, (float32) height1));
							ImGui::SameLine();
							if (ImGui::Selectable(audioIdentifiers [n].c_str(), selected_audio == n))
							{
								selected_audio = n;
							}
							if (ImGui::BeginDragDropSource())
							{
								selected_audio = n;
								const char* name = audioIdentifiers [n].c_str();
								ImGui::PushID(std::string("Project::Assets::Audios::" + audioIdentifiers [n]).c_str());
								ImGui::SetDragDropPayload("AssetAudioDragDrop", name, strlen(name) + 1);
								ImGui::PopID();
								ImGui::Text("%s", name);
								ImGui::EndDragDropSource();
							}
							if (ImGui::BeginPopupContextItem())
							{
								selected_audio = n;
								ImGui::Text("%s", audioIdentifiers [n].c_str());
								if (ImGui::Button("Copy"))
								{
									std::string name = audioIdentifiers [n];
									Audio* audio = AssetsManager::GetInstance().m_audio_mapper [name];
									AssetsManager::GetInstance().m_selected_audio = audio;
									ImGui::CloseCurrentPopup();
								}
								if (ImGui::Button("Remove"))
								{
									selected_audio = -1;
									AssetsManager::GetInstance().m_selected_audio = nullptr;
									std::string name = audioIdentifiers [n];
									Audio* audioTemp = AssetsManager::GetInstance().m_audio_mapper [name];
									delete audioTemp;
									AssetsManager::GetInstance().m_audio_mapper.erase(name);
								}
								if (ImGui::Button("Close"))
									ImGui::CloseCurrentPopup();
								ImGui::EndPopup();
							}
						}
					}
				}

				ImGui::EndChild();
			}
			ImGui::SameLine();
			{
				ImGui::BeginChild("Assets Details", ImVec2((float32) (width / 5 * 3), (float32) height - 35));

				std::map<std::string, Model*> modelMapper = AssetsManager::GetInstance().m_model_mapper;
				std::map<std::string, Shader*> shaderMapper = AssetsManager::GetInstance().m_shader_mapper;
				std::map<std::string, Texture*> textureMapper = AssetsManager::GetInstance().m_texture_mapper;
				std::map<std::string, Audio*> audioMapper = AssetsManager::GetInstance().m_audio_mapper;

				if (modelDetailsPanel)
				{
					float32 assetLineLength = 0;
					float32 assetImageSize = 64;
					for (std::pair<std::string, Model*> it_model : modelMapper)
					{
						ImGui::BeginChild(it_model.second->m_identifier.c_str(), ImVec2(assetImageSize, assetImageSize + height1));
						ImGui::Selectable(it_model.second->m_identifier.c_str(), false);
						if (ImGui::BeginDragDropSource())
						{
							const char* identifier = it_model.second->m_identifier.c_str();
							ImGui::PushID(std::string("Project::Details::Models::" + it_model.second->m_identifier).c_str());
							ImGui::SetDragDropPayload("AssetModelDragDrop", identifier, strlen(identifier) + 1);
							ImGui::PopID();
							ImGui::Text("%s", identifier);
							ImGui::EndDragDropSource();
						}
						ImGui::Image((ImTextureID) (intptr_t) m_image_model->m_ID, ImVec2(assetImageSize, assetImageSize));
						assetLineLength += (assetImageSize + 32);
						if ((width / 5 * 3) < assetLineLength)
						{
							assetLineLength = 0;
							ImGui::EndChild();
							ImGui::SetItemTooltip(it_model.second->m_identifier.c_str());
						}
						else
						{
							ImGui::EndChild();
							ImGui::SetItemTooltip(it_model.second->m_identifier.c_str());
							ImGui::SameLine();
						}
					}
				}

				if (shaderDetailsPanel)
				{
					float32 assetLineLength = 0;
					float32 assetImageSize = 64;
					for (std::pair<std::string, Shader*> it_shader : shaderMapper)
					{
						ImGui::BeginChild(it_shader.second->m_identifier.c_str(), ImVec2(assetImageSize, assetImageSize + height1));
						ImGui::Selectable(it_shader.second->m_identifier.c_str(), false);
						if (ImGui::BeginDragDropSource())
						{
							const char* identifier = it_shader.second->m_identifier.c_str();
							ImGui::PushID(std::string("Project::Details::Shaders::" + it_shader.second->m_identifier).c_str());
							ImGui::SetDragDropPayload("AssetShaderDragDrop", identifier, strlen(identifier) + 1);
							ImGui::PopID();
							ImGui::Text("%s", identifier);
							ImGui::EndDragDropSource();
						}
						ImGui::Image((ImTextureID) (intptr_t) m_image_file->m_ID, ImVec2(assetImageSize, assetImageSize));
						assetLineLength += (assetImageSize + 20);
						if ((width / 5 * 3) < assetLineLength)
						{
							assetLineLength = 0;
							ImGui::EndChild();
							ImGui::SetItemTooltip(it_shader.second->m_identifier.c_str());
						}
						else
						{
							ImGui::EndChild();
							ImGui::SetItemTooltip(it_shader.second->m_identifier.c_str());
							ImGui::SameLine();
						}
					}
				}

				if (textureDetailsPanel)
				{
					float32 assetLineLength = 0;
					float32 assetImageSize = 64;
					for (std::pair<std::string, Texture*> it_texture : textureMapper)
					{
						if (!it_texture.second->m_utility_image)
						{
							ImGui::BeginChild(it_texture.second->m_identifier.c_str(), ImVec2(assetImageSize, assetImageSize + height1));
							ImGui::Selectable(it_texture.second->m_identifier.c_str(), false);
							ImGui::Image((ImTextureID) (intptr_t) it_texture.second->m_ID, ImVec2(assetImageSize, assetImageSize));
							assetLineLength += (assetImageSize + 32);
							if ((width / 5 * 3) < assetLineLength)
							{
								assetLineLength = 0;
								ImGui::EndChild();
								ImGui::SetItemTooltip(it_texture.second->m_identifier.c_str());
							}
							else
							{
								ImGui::EndChild();
								ImGui::SetItemTooltip(it_texture.second->m_identifier.c_str());
								ImGui::SameLine();
							}
						}
					}
				}

				if (audioDetailsPanel)
				{
					float32 assetLineLength = 0;
					float32 assetImageSize = 64;
					for (std::pair<std::string, Audio*> it_audio : audioMapper)
					{
						ImGui::BeginChild(it_audio.second->GetIdentifier().c_str(), ImVec2(assetImageSize, assetImageSize + height1));
						ImGui::Selectable(it_audio.second->GetIdentifier().c_str(), false);
						if (ImGui::BeginDragDropSource())
						{
							std::string identifierStr = it_audio.second->GetIdentifier();
							const char* identifier = identifierStr.c_str();
							ImGui::PushID(std::string("Project::Details::Audios::" + it_audio.second->GetIdentifier()).c_str());
							ImGui::SetDragDropPayload("AssetAudioDragDrop", identifier, strlen(identifier) + 1);
							ImGui::PopID();
							ImGui::Text("%s", identifier);
							ImGui::EndDragDropSource();
						}
						ImGui::Image((ImTextureID) (intptr_t) m_image_audio->m_ID, ImVec2(assetImageSize, assetImageSize));
						assetLineLength += (assetImageSize + 32);
						if ((width / 5 * 3) < assetLineLength)
						{
							assetLineLength = 0;
							ImGui::EndChild();
							ImGui::SetItemTooltip(it_audio.second->GetIdentifier().c_str());
						}
						else
						{
							ImGui::EndChild();
							ImGui::SetItemTooltip(it_audio.second->GetIdentifier().c_str());
							ImGui::SameLine();
						}
					}
				}

				ImGui::EndChild();
			}
			ImGui::End();
		}
	}

	void UI::RenderConsolePanel(MainWindow* p_window)
	{
		int32 width = p_window->GetWindowWidth() / 10 * 4;
		int32 height = p_window->GetWindowHeight() / 3;
		ImGui::SetNextWindowPos(ImVec2((float32) (p_window->GetWindowWidth() - width), (float32) (p_window->GetWindowHeight() - height)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Console", &pOpen, windowFlags);

			ImGuiStyle& style = ImGui::GetStyle();
			style.Colors [ImGuiCol_Button] = ImVec4(0.495f, 0.289f, 0.289f, 1.0f);
			style.Colors [ImGuiCol_ButtonActive] = ImVec4(0.917f, 0.211f, 0.211f, 1.0f);
			style.Colors [ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
			if (ImGui::Button("Click ME"))
			{
				std::string url = "https://vdse.bdstatic.com//192d9a98d782d9c74c96f09db9378d93.mp4";
				std::string command = "start " + std::string(url);
				system(command.c_str());
			}
			style.Colors [ImGuiCol_Button] = ImVec4(0.289f, 0.289f, 0.289f, 1.0f);
			style.Colors [ImGuiCol_ButtonActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);
			style.Colors [ImGuiCol_ButtonHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);

			ImGui::Text("Camera Position: %.2f, %.2f, %.2f", p_window->GetCamera()->m_position.x, p_window->GetCamera()->m_position.y, p_window->GetCamera()->m_position.z);
			ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Ticks: %.5f   ", m_delta_time);
			ImGui::SameLine();
			float32 delta_time_factor = m_selected_scene->m_delta_time_factor;
			ImGui::DragFloat("##delta_time_factor", &delta_time_factor, 1.0f, 100.0f);
			if (delta_time_factor <= 0.0f)
				delta_time_factor = 1.0f;
			if (delta_time_factor >= 100.0f)
				delta_time_factor = 100.0f;
			m_selected_scene->m_delta_time_factor = delta_time_factor;

			if (ImGui::Button("Run"))
			{
				m_selected_scene->m_flag_stop = false;
				m_selected_scene->m_flag_run = true;
				g_tick_stop = false;
				g_tick_run = true;
				m_selected_scene->Active();
				glfwSetInputMode(p_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				m_editor_camera = p_window->GetCamera();
				p_window->SetCamera(m_player_camera);
			}
			ImGui::SameLine();
			if (ImGui::Button("Pause"))
			{
				m_selected_scene->m_flag_run = false;
				g_tick_run = false;
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop"))
			{
				m_selected_scene->m_flag_run = false;
				m_selected_scene->m_flag_stop = true;
				g_tick_run = false;
				g_tick_stop = true;
				glfwSetInputMode(p_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

				m_player_camera = p_window->GetCamera();
				p_window->SetCamera(m_editor_camera);
			}
			ImGui::SameLine();
			if (ImGui::Button("Export"))
			{
				std::vector<Scene*> scenes;
				for (std::pair<std::string, Scene*> it_scene : p_window->GetRenderPipeline()->m_scene_mapper)
				{
					scenes.push_back(it_scene.second);
				}
				Serializer* serializer = new Serializer();
				serializer->SetScenes(scenes);
				serializer->Serialize("./Assets/Configs/config3.json");
			}
			{
				ImGui::BeginChild("Console logout", ImVec2((float32) width, (float32) height - 132));
				
				ImGui::Text("%s", g_terminal_output.c_str());

				ImGui::EndChild();
			}

			ImGui::End();
		}
	}

	void UI::RenderGizmos(MainWindow* p_window)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::BeginFrame();
		if (m_selected_object != nullptr)
		{
			float32* cameraView = const_cast<float32*>(glm::value_ptr(m_window->GetCamera()->GetViewMatrix()));
			vec2f sceneSize = p_window->GetRenderPipeline()->GetSceneSize();
			mat4f projection = glm::perspective(glm::radians(m_window->GetCamera()->m_zoom),
												(float32) sceneSize.x / (float32) sceneSize.y,
												0.1f, 10000.0f);
			float32* cameraProjection = const_cast<float32*>(glm::value_ptr(projection));
			TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(m_selected_object->GetComponents().find("Transform")->second);
			float32* objectModelMatrix = const_cast<float32*>(glm::value_ptr(transformComponent->GetMatrix()));
			m_gizmos->EditTransform(p_window, cameraView, cameraProjection, objectModelMatrix, true);
			transformComponent->SetPosition(m_gizmos->GetPosition());
			transformComponent->SetRotation(m_gizmos->GetRotation());
			transformComponent->SetScale(m_gizmos->GetScale());
		}
	}

	void UI::RenderAddingComponentsPanel(MainWindow* p_window)
	{
		int32 width = 200;
		int32 height = 200;
		int32 textHeight = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGui::SetNextWindowPos(ImVec2((float32) (p_window->GetWindowWidth() / 2 - 100), (float32) (p_window->GetWindowHeight() / 2 - 100)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Component", &m_show_adding_component_panel, windowFlags);

			bool disableAudio = m_selected_object->HasComponent("Audio");
			if (disableAudio)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("Audio", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				AudioComponent* audioComponentTemp = new AudioComponent();
				m_selected_object->AddComponent(audioComponentTemp);
			}
			if (disableAudio)
			{
				ImGui::EndDisabled();
			}
			bool disableCamera = m_selected_object->HasComponent("Camera");
			if (disableCamera)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("Camera", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				CameraComponent* cameraComponentTemp = new CameraComponent();
				m_selected_object->AddComponent(cameraComponentTemp);
			}
			if (disableCamera)
			{
				ImGui::EndDisabled();
			}
			bool disableCharacterController = m_selected_object->HasComponent("CharacterController");
			if (disableCharacterController)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("CharacterController", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				CharacterControllerComponent* characterControllerComponentTemp = new CharacterControllerComponent();
				m_selected_object->AddComponent(characterControllerComponentTemp);
			}
			if (disableCharacterController)
			{
				ImGui::EndDisabled();
			}
			bool disableLight = m_selected_object->HasComponent("Light");
			if (disableLight)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("Light", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				LightComponent* lightComponentTemp = new LightComponent();
				m_selected_object->AddComponent(lightComponentTemp);
			}
			if (disableLight)
			{
				ImGui::EndDisabled();
			}
			bool disableModel = m_selected_object->HasComponent("Model");
			if (disableModel)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("Model", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				ModelComponent* modelComponentTemp = new ModelComponent();
				m_selected_object->AddComponent(modelComponentTemp);
			}
			if (disableModel)
			{
				ImGui::EndDisabled();
			}
			bool disablePhysics = m_selected_object->HasComponent("Physics");
			if (disablePhysics)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("Physics", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				PhysicsComponent* physicsComponentTemp = new PhysicsComponent();
				m_selected_object->AddComponent(physicsComponentTemp);
			}
			if (disablePhysics)
			{
				ImGui::EndDisabled();
			}
			bool disableShader = m_selected_object->HasComponent("Shader");
			if (disableShader)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("Shader", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				ShaderComponent* shaderComponentTemp = new ShaderComponent();
				m_selected_object->AddComponent(shaderComponentTemp);
			}
			if (disableShader)
			{
				ImGui::EndDisabled();
			}
			bool disableTransform = m_selected_object->HasComponent("Transform");
			if (disableTransform)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Button("Transform", ImVec2((float32) width - 15, (float32) textHeight)))
			{
				TransformComponent* transformComponent = new TransformComponent();
				m_selected_object->AddComponent(transformComponent);
			}
			if (disableTransform)
			{
				ImGui::EndDisabled();
			}


			ImGui::End();
		}
	}

	void UI::InitImages()
	{
		m_button_image_reset = AssetsManager::GetInstance().m_texture_mapper ["reset.png"];
		m_image_folder = AssetsManager::GetInstance().m_texture_mapper ["folder.png"];
		m_image_folder_close = AssetsManager::GetInstance().m_texture_mapper ["folder_close.png"];
		m_image_empty_file = AssetsManager::GetInstance().m_texture_mapper ["empty_file.png"];
		m_image_file = AssetsManager::GetInstance().m_texture_mapper ["file.png"];
		m_image_audio = AssetsManager::GetInstance().m_texture_mapper ["audio.png"];
		m_image_model = AssetsManager::GetInstance().m_texture_mapper ["model.png"];
	}

	void UI::ShowDemoWindow()
	{
		ImVec4 backgroungColor(0.725f, 0.725f, 0.725f, 1.0f);

		if (m_show_demo_window)
		{
			ImGui::ShowDemoWindow(&m_show_demo_window);
		}
	}
}

/*
Hierachy
	SceneList
		Scene 1
			Obj1
			Obj2
		Scene 2
			Obj1
			Obj2
*/
/*
Inspector
	Transform
		Position
		Rotation
		Scale
	Renderer
		Texture
		Materials
			Shader
*/
/*
Project
	(Folder)Assets
	Packages
*/
/*
Console
	Clear | Collapse | Error Pause | Editor
*/
/*
Game
	Game | Display 1 | Free Aspect | Scale
*/