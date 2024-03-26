#define GLFW_INCLUDE_NONE

#include <Types.hpp>
#include <UI.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>
#include <Windows.h>

namespace fs = std::filesystem;
namespace Spore
{
	const char* glsl_version = "#version 130";

	UI::UI(MainWindow* window_p)
	{
		InitImGui(window_p);
	}

	UI::~UI()
	{

	}

	void UI::InitImGui(MainWindow* window_p)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

		//ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window_p->window, true);
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
		style.Colors [ImGuiCol_ChildBg] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_Header] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_HeaderActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);
		style.Colors [ImGuiCol_HeaderHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);
		style.Colors [ImGuiCol_FrameBg] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_FrameBgActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);
		style.Colors [ImGuiCol_FrameBgHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);
		style.Colors [ImGuiCol_Tab] = ImVec4(0.382f, 0.382f, 0.382f, 1.0f);
		style.Colors [ImGuiCol_TabActive] = ImVec4(0.320f, 0.320f, 0.320f, 1.0f);
		style.Colors [ImGuiCol_TabHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);
		style.Colors [ImGuiCol_SliderGrab] = ImVec4(0.289f, 0.289f, 0.289f, 1.0f);
		style.Colors [ImGuiCol_SliderGrabActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);


	#ifdef __EMSCRIPTEN__
		ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
	#endif
	}

	void UI::UITerminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UI::InitPanels(MainWindow* window_p)
	{
		/*int32 displayW, displayH;
		glfwGetFramebufferSize(window_p->window, &displayW, &displayH);
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = displayW;
		io.DisplaySize.y = displayH;*/

		RenderMenuBar(window_p);
		RenderHierarchyPanel(window_p);
		//RenderScenePanel(window);
		RenderInspectorPanel(window_p);
		RenderProjectPanel(window_p);
		RenderConsolePanel(window_p);
	}

	void UI::RenderMenuBar(MainWindow* window_p)
	{
		int32 width = window_p->width;
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
					ImGui::SeparatorText("");
					ImGui::MenuItem("Save", NULL, false, true);
					ImGui::MenuItem("Save As...", NULL, false, true);
					ImGui::MenuItem("Save As Scene Template...", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("New Project...", NULL, false, true);
					ImGui::MenuItem("Open Project...", NULL, false, true);
					ImGui::MenuItem("Save Project", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Build Settings...", NULL, false, true);
					ImGui::MenuItem("Build And Run", NULL, false, true);
					ImGui::SeparatorText("");
					if (ImGui::MenuItem("Exit"))
					{
						glfwSetWindowShouldClose(window_p->window, true);
					}

					ImGui::SeparatorText("============");
					ImGui::SeparatorText("============");
					if (ImGui::MenuItem("Import Model"))
					{
						/*importAssetsPath = Files::GetInstance().GetAssetsPath() / "Models";
						filePath = &importAssetsPath;*/
						showImportModelPanel = true;
					}
					if (ImGui::MenuItem("Import Shader"))
					{
						showImportShaderPanel = true;
					}
					if (ImGui::MenuItem("Import Texture"))
					{
						showImportTexturePanel = true;
					}
					ImGui::SeparatorText("General Setting");
					ImGui::Checkbox("Show Skybox", &window_p->renderPipeline->skyboxOn);
					ImGui::Checkbox("Gamma Correction", &window_p->renderPipeline->gammaCorrection);
					ImGui::SliderFloat("Camera Speed", &window_p->camera->MovementSpeed, 0.0f, 50.0f);
					static int32 windowSizeIndex = -1;
					ImGui::Checkbox("Console", &showConsole);
					ImGui::SeparatorText("============");
					ImGui::SeparatorText("============");

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Edit"))
				{
					ImGui::MenuItem("Undo Clear Selection", NULL, false, true);
					ImGui::MenuItem("Redo", NULL, false, true);
					ImGui::MenuItem("Undo History", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Select All", NULL, false, true);
					ImGui::MenuItem("Deselect All", NULL, false, true);
					ImGui::MenuItem("Select Children", NULL, false, true);
					ImGui::MenuItem("Select Prefab Root", NULL, false, true);
					ImGui::MenuItem("Invert Selection", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Cut", NULL, false, true);
					ImGui::MenuItem("Copy", NULL, false, true);
					ImGui::MenuItem("Paste", NULL, false, true);
					ImGui::MenuItem("Paste As Child", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Duplicate", NULL, false, true);
					ImGui::MenuItem("Rename", NULL, false, true);
					ImGui::MenuItem("Delete", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Frame Selected", NULL, false, true);
					ImGui::MenuItem("Lock View to Selected", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Find", NULL, false, true);
					ImGui::MenuItem("Search All...", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Play", NULL, false, true);
					ImGui::MenuItem("Pause", NULL, false, true);
					ImGui::MenuItem("Step", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Sign in...", NULL, false, true);
					ImGui::MenuItem("Sign out", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Selection", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Project Settings...", NULL, false, true);
					ImGui::MenuItem("Preferences...", NULL, false, true);
					ImGui::MenuItem("Shortcuts...", NULL, false, true);
					ImGui::MenuItem("Clear All PlayerPrefs", NULL, false, true);
					ImGui::SeparatorText("");
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
					ImGui::SeparatorText("");
					ImGui::MenuItem("Open Scene Additive", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("View in Package Manager", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Import New Asset...", NULL, false, true);
					ImGui::MenuItem("Import Package", NULL, false, true);
					ImGui::MenuItem("Export Package...", NULL, false, true);
					ImGui::MenuItem("Find References In Scene", NULL, false, true);
					ImGui::MenuItem("Select Dependencies", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Refresh", NULL, false, true);
					ImGui::MenuItem("Reimport", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Reimport All", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Extract From Prefab", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Update UXML Schema", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Open C# Project", NULL, false, true);
					ImGui::MenuItem("View in Import Activity Window", NULL, false, true);
					ImGui::SeparatorText("");
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
					ImGui::SeparatorText("");
					ImGui::MenuItem("Center On Children", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Make Parent", NULL, false, true);
					ImGui::MenuItem("Clear Parent", NULL, false, true);
					ImGui::SeparatorText("");
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
					ImGui::SeparatorText("");
					ImGui::MenuItem("Next Window", NULL, false, true);
					ImGui::MenuItem("Previous Window", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Layouts", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Search", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Collaborate", NULL, false, true);
					ImGui::MenuItem("Plastic SCM", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Asset Store", NULL, false, true);
					ImGui::MenuItem("Package Manager", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Asset Management", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Text", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("TextMeshPro", NULL, false, true);
					ImGui::SeparatorText("");
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
					ImGui::SeparatorText("");
					ImGui::MenuItem("Check for Updates", NULL, false, true);
					ImGui::MenuItem("Download Beta...", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Manage License", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Release Notes", NULL, false, true);
					ImGui::MenuItem("Software Licenses", NULL, false, true);
					ImGui::MenuItem("Report a Bug...", NULL, false, true);
					ImGui::SeparatorText("");
					ImGui::MenuItem("Reset Packages to defaults", NULL, false, true);
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}
	}

	void UI::RenderHierarchyPanel(MainWindow* window_p)
	{
		int32 width = window_p->width / 6 > 200 ? window_p->width / 6 : 200;
		int32 height = window_p->height / 3 * 2 > 400 ? window_p->height / 3 * 2 : 400;
		int32 height1 = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGui::SetNextWindowPos(ImVec2(0.0f, (float32) height1), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) (height - height1)), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Hierarchy", &pOpen, windowFlags);
			std::shared_ptr<Scene> scene = window_p->renderPipeline->sceneMapper.find("scene1")->second;
			std::vector<std::string> objectIdentifiers;
			std::map<std::string, std::shared_ptr<Object>>* objectMapper = &scene->objectMapper;
			for (std::map<std::string, std::shared_ptr<Object>>::iterator it = objectMapper->begin(); it != objectMapper->end(); it++)
			{
				objectIdentifiers.push_back(it->first);
			}
			if (selectedObjectIndex >= 0)
			{
				selectedObject = scene->objectMapper.find(objectIdentifiers [selectedObjectIndex])->second;
				selectedObject->selected = true;
			}
			if (ImGui::CollapsingHeader("Scene", true))
			{
				for (int i = 0; i < objectIdentifiers.size(); i++)
				{
					const char* objIdentifier = objectIdentifiers [i].c_str();
					if (ImGui::Selectable(objIdentifier, selectedObjectIndex == i))
					{
						selectedObjectIndex = i;
					}
					if (ImGui::BeginPopupContextItem())
					{
						selectedObjectIndex = i;
						ImGui::Text("%s", objectIdentifiers [i].c_str());
						if (ImGui::Button("Remove"))
						{
							std::string name = objectIdentifiers [i];
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
							AssetsManager::GetInstance().modelCounter [subName]--;
							//scene->objectMapper.erase(name);
							objectMapper->erase(name);
							objectIdentifiers.erase(std::remove(objectIdentifiers.begin(), objectIdentifiers.end(), name), objectIdentifiers.end());
							selectedObjectIndex = -1;
						}
						if (ImGui::Button("Close"))
							ImGui::CloseCurrentPopup();
						ImGui::EndPopup();
					}
					ImGui::SetItemTooltip("Right-click to open popup");
				}
			}
			ImGui::End();
		}
	}

	void UI::RenderScenePanel(MainWindow* window_p)
	{

	}

	void UI::RenderInspectorPanel(MainWindow* window_p)
	{
		int32 width = window_p->width / 6 > 200 ? window_p->width / 6 : 200;
		int32 height = window_p->height / 3 * 2 > 400 ? window_p->height / 3 * 2 : 400;
		int32 height1 = (int32) (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().FramePadding.y * 0.5f);
		ImGui::SetNextWindowPos(ImVec2((float32) (window_p->width - width), (float32) height1), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) (height - height1)), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Inspector", &pOpen, windowFlags);

			if (selectedObject != nullptr)
			{
				if (ImGui::CollapsingHeader(selectedObject->identifier.c_str(), true))
				{
					ImGui::Text("Type: %s", selectedObject->type.c_str());
					ImGui::Separator();
					ImGui::Text("Models");
					for (std::pair<std::string, Model*> it_model : selectedObject->modelMapper)
					{
						ImGui::Text(it_model.second->identifier.c_str());
						ImGui::Separator();
					}
					ImGui::Text("Layer");
					const char* layers [] = {
						"Default",
						"TransparentFX",
						"UI",
						"PostProcessing",
						"Terrain",
						"Background"
					};
					static int currentLayer = 0;
					if (ImGui::BeginCombo("##Layer", layers[currentLayer]))
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
				}
				if (ImGui::CollapsingHeader("Transform", true))
				{
					vec3f pos = selectedObject->GetPosition();
					float position [3] = { pos.x, pos.y, pos.z };
					ImGui::Text("Position");
					ImGui::PushID("Inspector:Transform:Position");
					ImGui::DragFloat3("", position, 0.1f);
					ImGui::PopID();
					selectedObject->SetPosition(vec3f(position [0], position [1], position [2]));
					vec3f rot = selectedObject->GetRotation();
					float rotation [3] = { rot.x, rot.y, rot.z };
					ImGui::Text("Rotation");
					ImGui::PushID("Inspector:Transform:Rotation");
					ImGui::DragFloat3("", rotation, 0.1f);
					ImGui::PopID();
					selectedObject->SetRotation(vec3f(rotation [0], rotation [1], rotation [2]));
					vec3f sca = selectedObject->GetScale();
					float scale [3] = { sca.x, sca.y, sca.z };
					ImGui::Text("Scale");
					ImGui::PushID("Inspector:Transform:Scale");
					ImGui::DragFloat3("", scale, 0.1f);
					ImGui::PopID();
					selectedObject->SetScale(vec3f(scale [0], scale [1], scale [2]));
				}
				std::unordered_map<std::string, Component*> components = selectedObject->GetComponents();
				if (ImGui::CollapsingHeader("Shader", true))
				{
					ShaderComponent* shaderComponent = dynamic_cast<ShaderComponent*>(components.find("Shader")->second);
					for (std::pair<std::string, ShaderNode*> it_shader : shaderComponent->GetShaders())
					{
						ImGui::Text(it_shader.second->shader->identifier.c_str());
						ImGui::Checkbox("Is dLoading", &it_shader.second->isLoading);
						ImGui::Checkbox("Alpha Filter", &it_shader.second->shader->alphaFilterFlag);
						ImGui::Separator();
					}
				}

			}

			ImGui::End();
		}
	}

	void UI::RenderProjectPanel(MainWindow* window_p)
	{
		int32 width = window_p->width / 10 * 6 > 200 ? window_p->width / 10 * 6 : 200;
		int32 height = window_p->height / 3 > 300 ? window_p->height / 3 : 300;
		ImGui::SetNextWindowPos(ImVec2(0.0f, (float32) (window_p->height - height)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Always);
		ImGuiWindowFlags windowFlags = 0;
		static bool pOpen = true;
		windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
		{
			ImGui::Begin("Project", &pOpen, windowFlags);
			std::vector<std::string> shaderIdentifiers;
			std::vector<std::string> textureIdentifiers;
			std::vector<std::string> modelIdentifiers;
			std::map<std::string, Shader*> shaderMapper = AssetsManager::GetInstance().shaderMapper;
			for (std::map<std::string, Shader*>::iterator it = shaderMapper.begin(); it != shaderMapper.end(); it++)
			{
				shaderIdentifiers.push_back(it->first);
			}
			std::map<std::string, Texture*> textureMapper = AssetsManager::GetInstance().textureMapper;
			for (std::map<std::string, Texture*>::iterator it = textureMapper.begin(); it != textureMapper.end(); it++)
			{
				textureIdentifiers.push_back(it->first);
			}
			std::map<std::string, Model*> modelMapper = AssetsManager::GetInstance().modelMapper;
			for (std::map<std::string, Model*>::iterator it = modelMapper.begin(); it != modelMapper.end(); it++)
			{
				modelIdentifiers.push_back(it->first);
			}
			if (ImGui::CollapsingHeader("Assets", true))
			{
				if (ImGui::CollapsingHeader("Models", true))
				{
					static int32 selected_model = -1;
					for (uint32 n = 0; n < modelIdentifiers.size(); n++)
					{
						if (ImGui::Selectable(modelIdentifiers [n].c_str(), selected_model == n))
							selected_model = n;
						if (ImGui::BeginPopupContextItem())
						{
							selected_model = n;
							ImGui::Text("%s", modelIdentifiers [n].c_str());
							if (ImGui::Button("Create Object"))
							{
								std::string name = modelIdentifiers [n];
								int32 modelCount = ++AssetsManager::GetInstance().modelCounter [name];
								std::shared_ptr<Object> object = std::make_shared<Object>("obj_" + std::to_string(modelCount) + "_" + modelMapper [name]->identifier);
								std::shared_ptr<Scene> scene = window_p->renderPipeline->sceneMapper.find("scene1")->second;
								object->AddModel(modelMapper [name]);
								scene->AddObject(object);
								modelMapper [name]->AddObserver(object);
								object->AddObserver(scene);
								ImGui::CloseCurrentPopup();
							}
							if (ImGui::Button("Remove"))
							{
								selected_model = -1;
								selectedObjectIndex = -1;
								selectedObject = nullptr;
								std::string name = modelIdentifiers [n];
								Model* modelTemp = AssetsManager::GetInstance().modelMapper [name];
								delete modelTemp;
								AssetsManager::GetInstance().modelMapper.erase(name);
							}
							if (ImGui::Button("Close"))
								ImGui::CloseCurrentPopup();
							ImGui::EndPopup();
						}
						ImGui::SetItemTooltip("Right-click to open popup");
					}
				}
				if (ImGui::CollapsingHeader("Shaders", true))
				{
					static int32 selected_shader = -1;
					for (uint32 n = 0; n < shaderIdentifiers.size(); n++)
					{
						if (ImGui::Selectable(shaderIdentifiers [n].c_str(), selected_shader == n))
							selected_shader = n;
						if (ImGui::BeginPopupContextItem())
						{
							selected_shader = n;
							ImGui::Text("%s", shaderIdentifiers [n].c_str());
							if (ImGui::Button("Refresh"))
							{
								//Utils::AssetsManager::GetInstance().shaderMapper [shaderID [n]]->Refresh();
								ImGui::CloseCurrentPopup();
							}
							if (ImGui::Button("Remove"))
							{
								Shader* tmp = AssetsManager::GetInstance().shaderMapper [shaderIdentifiers [n]];
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
						ImGui::SetItemTooltip("Right-click to open popup");
					}
				}
				if (ImGui::CollapsingHeader("Textures", true))
				{
					static int32 selected_tex = -1;
					{
						for (uint32 n = 0; n < textureIdentifiers.size(); n++)
						{
							if (ImGui::Selectable(textureIdentifiers [n].c_str(), selected_tex == n))
								selected_tex = n;
							if (ImGui::BeginPopupContextItem())
							{
								selected_tex = n;
								ImGui::Text("%s", textureIdentifiers [n].c_str());
								if (ImGui::Button("Remove"))
								{
									Texture* tmp = AssetsManager::GetInstance().textureMapper [textureIdentifiers [n]];
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
							ImGui::SetItemTooltip("Right-click to open popup");
						}
					}
				}
			}
			//ImGui::SetNextWindowSize(ImVec2(width, height / 3 * 2), ImGuiCond_Always);
			//{
			//	float32 previewWidth = width / 3 * 2;
			//	float32 previewHeight = height / 3 * 2;
			//	ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_None;
			//	if (ImGui::BeginTabBar("Assets Bar", tabBarFlags))
			//	{
			//		if (ImGui::BeginTabItem("Loaded Shaders"))
			//		{
			//			static int32 selected_shader = -1;
			//			for (uint32 n = 0; n < shaderIdentifiers.size(); n++)
			//			{
			//				if (ImGui::Selectable(shaderIdentifiers [n].c_str(), selected_shader == n))
			//					selected_shader = n;
			//				if (ImGui::BeginPopupContextItem())
			//				{
			//					selected_shader = n;
			//					ImGui::Text("This a popup for \"%s\"!", shaderIdentifiers [n].c_str());
			//					if (ImGui::Button("Refresh"))
			//					{
			//						//Utils::AssetsManager::GetInstance().shaderMapper [shaderID [n]]->Refresh();
			//						ImGui::CloseCurrentPopup();
			//					}
			//					if (ImGui::Button("Remove"))
			//					{
			//						Shader* tmp = AssetsManager::GetInstance().shaderMapper [shaderIdentifiers [n]];
			//						/*if (!tmp->IsEditor())
			//						{
			//							selected_shader = -1;
			//							delete tmp;
			//						}
			//						else
			//						{
			//							RendererConsole::GetInstance()->AddError("[error] Editor Shader can not be removed!");
			//						}*/
			//					}
			//					if (ImGui::Button("Close"))
			//						ImGui::CloseCurrentPopup();
			//					ImGui::EndPopup();
			//				}
			//				ImGui::SetItemTooltip("Right-click to open popup");
			//			}
			//			ImGui::EndTabItem();
			//		}

			//		if (ImGui::BeginTabItem("Loaded Textures"))
			//		{
			//			static int32 selected_tex = -1;
			//			{
			//				ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
			//				ImGui::BeginChild("TextureList", ImVec2(ImGui::GetContentRegionAvail().x - previewWidth, previewHeight), ImGuiChildFlags_None, window_flags);
			//				for (uint32 n = 0; n < textureIdentifiers.size(); n++)
			//				{
			//					if (ImGui::Selectable(textureIdentifiers [n].c_str(), selected_tex == n))
			//						selected_tex = n;
			//					if (ImGui::BeginPopupContextItem())
			//					{
			//						selected_tex = n;
			//						ImGui::Text("This a popup for \"%s\"!", textureIdentifiers [n].c_str());
			//						if (ImGui::Button("Remove"))
			//						{
			//							Texture* tmp = AssetsManager::GetInstance().textureMapper [textureIdentifiers [n]];
			//							/*if (!tmp->is_editor)
			//							{
			//								selected_tex = -1;
			//								delete tmp;
			//							}
			//							else
			//							{
			//								RendererConsole::GetInstance()->AddError("[error] Editor Texture can not be deleted!");
			//							}*/
			//						}
			//						if (ImGui::Button("Close"))
			//							ImGui::CloseCurrentPopup();
			//						ImGui::EndPopup();
			//					}
			//					ImGui::SetItemTooltip("Right-click to open popup");
			//				}
			//				ImGui::EndChild();
			//			}

			//			//ImGui::SameLine();
			//			//{
			//			//	if (selected_tex >= 0)
			//			//	{
			//			//		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			//			//		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			//			//		ImGui::BeginChild("TexturePreviewPanel", ImVec2(preview_width - 10, preview_height - 20), ImGuiChildFlags_Border, window_flags);
			//			//		Texture2D* tex = Texture2D::LoadedTextures [tex_names [selected_tex]];
			//			//		ImGui::BeginChild("TextureInfo", ImVec2(preview_width - preview_height, preview_height - 40), ImGuiChildFlags_Border);
			//			//		ImGui::Text(("name:" + tex->name).c_str());
			//			//		ImGui::Text(("ref count:" + std::to_string(tex->textureRefs.references.size())).c_str());
			//			//		ImGui::Text(("path:" + tex->path).c_str());

			//			//		const char* types [] = { "RED", "RGB", "RGBA", "SRGB", "SRGBA" };
			//			//		static int type_idx = -1;
			//			//		const char* cur_type = types [tex->tex_type];
			//			//		if (ImGui::BeginCombo("type", cur_type))
			//			//		{
			//			//			for (int n = 0; n < 5; n++)
			//			//			{
			//			//				if (ImGui::Selectable(types [n], false))
			//			//				{
			//			//					tex->tex_type = (ETexType) n;
			//			//					tex->ResetTextureType(tex->tex_type);
			//			//				}
			//			//			}
			//			//			ImGui::EndCombo();
			//			//		}

			//			//		ImGui::Text(("width:" + std::to_string(tex->width)).c_str());
			//			//		ImGui::Text(("height:" + std::to_string(tex->height)).c_str());
			//			//		ImGui::EndChild();

			//			//		ImGui::SameLine();

			//			//		ImGui::BeginChild("TexturePreview", ImVec2(preview_height - 40, preview_height - 40), ImGuiChildFlags_Border);
			//			//		float width = preview_height - 60;
			//			//		float height = preview_height - 60;
			//			//		ImVec2 uv_min = ImVec2(0.0f, 0.0f);                        // Top-left
			//			//		ImVec2 uv_max = ImVec2(1.0f, 1.0f);                        // Lower-right
			//			//		ImVec4 tint_col = ImGui::GetStyleColorVec4(ImGuiCol_Text); // No tint
			//			//		ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			//			//		ImGui::Image((GLuint*) tex->id, ImVec2(width, height), uv_min, uv_max, tint_col, border_col);
			//			//		ImGui::EndChild();
			//			//		ImGui::EndChild();
			//			//		ImGui::PopStyleVar();
			//			//	}
			//			//}
			//			ImGui::EndTabItem();
			//		}
			//		if (ImGui::BeginTabItem("Loaded Models"))
			//		{
			//			ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
			//			ImGui::BeginChild("ModelList", ImVec2(ImGui::GetContentRegionAvail().x - previewWidth, previewHeight), ImGuiChildFlags_None, window_flags);
			//			static int32 selected_model = -1;
			//			for (uint32 n = 0; n < modelIdentifiers.size(); n++)
			//			{
			//				if (ImGui::Selectable(modelIdentifiers [n].c_str(), selected_model == n))
			//					selected_model = n;
			//				if (ImGui::BeginPopupContextItem())
			//				{
			//					selected_model = n;
			//					ImGui::Text("This a popup for \"%s\"!", modelIdentifiers [n].c_str());
			//					if (ImGui::Button("Create Instance"))
			//					{
			//						std::string name = modelIdentifiers [n];
			//						std::shared_ptr<Object> object = std::make_shared<Object>("obj_" + modelMapper [name]->identifier);
			//						std::shared_ptr<Scene> scene = window_p->renderPipeline->sceneMapper.find("scene1")->second;
			//						if (scene->objectMapper.find(object->identifier) !=
			//							scene->objectMapper.end())
			//						{
			//							scene->objectMapper.find(object->identifier)->second->AddModel(modelMapper [name]);
			//						}
			//						else
			//						{
			//							object->AddModel(modelMapper [name]);
			//							scene->AddObject(object);
			//						}
			//						modelMapper [name]->AddObserver(object);
			//						object->AddObserver(scene);
			//						ImGui::CloseCurrentPopup();
			//					}
			//					if (ImGui::Button("Remove"))
			//					{
			//						selected_model = -1;
			//						std::string name = modelIdentifiers [n];
			//						Model* modelTemp = AssetsManager::GetInstance().modelMapper [name];
			//						delete modelTemp;
			//						AssetsManager::GetInstance().modelMapper.erase(name);
			//					}
			//					if (ImGui::Button("Close"))
			//						ImGui::CloseCurrentPopup();
			//					ImGui::EndPopup();
			//				}
			//				ImGui::SetItemTooltip("Right-click to open popup");
			//			}
			//			ImGui::EndChild();

			//			ImGui::SameLine();

			//			if (selected_model >= 0)
			//			{
			//				window_flags = ImGuiWindowFlags_None;
			//				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			//				ImGui::BeginChild("ModelPreviewPanel", ImVec2(previewWidth - 10, previewHeight - 20), ImGuiChildFlags_Border, window_flags);
			//				ImGui::BeginChild("ModelInfo", ImVec2(previewWidth - 20, previewHeight - 40), ImGuiChildFlags_Border);
			//				Model* cur_model = AssetsManager::GetInstance().modelMapper [modelIdentifiers [selected_model]];
			//				ImGui::Text(("name:" + cur_model->identifier).c_str());
			//				ImGui::Text(("mesh count:" + std::to_string(cur_model->meshes.size())).c_str());
			//				//ImGui::Text(("ref count:" + std::to_string(cur_model->refSceneModels.references.size())).c_str());
			//				//ImGui::Text(("loaded textures:" + std::to_string(cur_model->textures_loaded.size())).c_str());
			//				ImGui::Text(("directory:" + cur_model->directory).c_str());
			//				ImGui::EndChild();
			//				ImGui::EndChild();
			//				ImGui::PopStyleVar();
			//			}
			//			ImGui::EndTabItem();
			//		}
			//		ImGui::EndTabBar();
			//	}
			//}
			ImGui::End();
		}
		ImportShaderPanel(window_p);
		ImportTexturePanel(window_p);
		ImportModelPanel(window_p);
		FileBrowser(window_p, filePath);
	}

	void UI::RenderConsolePanel(MainWindow* window_p)
	{
		int32 width = window_p->width / 10 * 4 > 200 ? window_p->width / 10 * 4 : 200;
		int32 height = window_p->height / 3 > 300 ? window_p->height / 3 : 300;
		ImGui::SetNextWindowPos(ImVec2((float32) (window_p->width - width), (float32) (window_p->height - height)), ImGuiCond_Always);
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
			/*if (ImGui::Button("Click ME"))
			{
				std::string url = "https://vdse.bdstatic.com//192d9a98d782d9c74c96f09db9378d93.mp4";
				std::string command = "start " + std::string(url);
				system(command.c_str());
			}*/
			style.Colors [ImGuiCol_Button] = ImVec4(0.289f, 0.289f, 0.289f, 1.0f);
			style.Colors [ImGuiCol_ButtonActive] = ImVec4(0.511f, 0.511f, 0.511f, 1.0f);
			style.Colors [ImGuiCol_ButtonHovered] = ImVec4(0.422f, 0.422f, 0.422f, 1.0f);

			ImGui::Text("Camera Position: %.2f, %.2f, %.2f", window_p->camera->Position.x, window_p->camera->Position.y, window_p->camera->Position.z);
			ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}
	}

	void UI::ShowDemoWindow()
	{
		ImVec4 backgroungColor(0.725f, 0.725f, 0.725f, 1.0f);

		bool show_demo_window = true;
		bool show_another_window = false;

		if (show_demo_window)
		{
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		// show a simple window
		{
			static float32 f = 0.0f;
			static int32 counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

			ImGui::ColorEdit3("clear color", (float32*) &backgroungColor); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::End();
		}
	}

	void UI::ImportModelPanel(MainWindow* window_p)
	{
		if (!showImportModelPanel)
			return;
		int32 width = 700;
		int32 height = 400;
		ImGui::SetNextWindowPos(ImVec2((float32) ((window_p->width - width) / 2), (float32) ((window_p->height - height) / 2)), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Appearing);
		{
			ImGui::Begin("Import Model");
			static char model_path [128];
			strcpy_s(model_path, importAssetsPath.string().c_str());
			static std::string info = "";
			//try
			//{
			//	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

			//	if (ImGui::Button(".."))
			//	{
			//		*filePath = filePath->parent_path();
			//	}
			//	ImGui::SameLine();
			//	std::vector<fs::path> roots = Files::GetInstance().GetRootPaths();
			//	int32 rootNum = (int32) roots.size();
			//	static int32 rootIndex = 0;
			//	if (ImGui::BeginCombo("root paths", filePath->string().c_str()))
			//	{
			//		for (int32 n = 0; n < rootNum; n++)
			//		{
			//			const bool isSelected = (rootIndex == n);
			//			if (ImGui::Selectable(roots [n].string().c_str(), isSelected))
			//			{
			//				rootIndex = n;
			//				*filePath = fs::path(roots [n].string().c_str());
			//			}
			//			if (isSelected)
			//				ImGui::SetItemDefaultFocus();
			//		}
			//		ImGui::EndCombo();
			//	}
			//	std::vector<fs::directory_entry> files;
			//	for (auto const& dir_entry : fs::directory_iterator { *filePath })
			//	{
			//		files.push_back(dir_entry);
			//	}
			//	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_HorizontalScrollbar;
			//	ImGui::BeginChild("FileList", ImVec2((float32) (width - 50), (float32) (height - 100)), ImGuiChildFlags_Border, windowFlags);
			//	static int32 selectedFile = -1;
			//	for (uint32 i = 0; i < files.size(); i++)
			//	{
			//		std::string fileName = files [i].path().filename().string();
			//		float32 witdh = 16;
			//		float32 height = 16;
			//		ImVec2 uvMin = ImVec2(0.0f, 0.0f);
			//		ImVec2 uvMax = ImVec2(1.0f, 1.0f);
			//		ImVec4 tintCol = ImGui::GetStyleColorVec4(ImGuiCol_Text);
			//		/*if (fs::is_directory(files [i]))
			//		{
			//		}
			//		else
			//		{
			//		}
			//		ImGui::SameLine();*/
			//		if (ImGui::Selectable(fileName.c_str(), selectedFile == i))
			//		{
			//			if (selectedFile == i)
			//			{
			//				if (fs::is_directory(files [selectedFile]))
			//				{
			//					*filePath = files [selectedFile].path();
			//				}
			//				else
			//				{
			//					*filePath = files [selectedFile].path();
			//					showImportModelPanel = false;
			//				}
			//				selectedFile = -1;
			//			}
			//			else
			//			{
			//				selectedFile = i;
			//			}
			//		}
			//	}
			//	ImGui::EndChild();
			//	if (ImGui::Button("Cancel"))
			//	{
			//		showImportModelPanel = false;
			//	}
			//	ImGui::SameLine();
			//	if (ImGui::Button("Confirm"))
			//	{
			//		if (selectedFile != -1)
			//		{
			//			if (fs::is_directory(files [selectedFile]))
			//			{
			//				*filePath = files [selectedFile].path();
			//			}
			//			else
			//			{
			//				*filePath = files [selectedFile].path();
			//				showImportModelPanel = false;
			//			}
			//			selectedFile = -1;
			//		}
			//		else
			//		{
			//			showImportModelPanel = false;
			//		}
			//	}
			//	ImGui::PopStyleVar();
			//}
			//catch (const std::filesystem::filesystem_error& ex)
			//{
			//	std::cerr << "Filesystem error: " << ex.what() << std::endl;
			//}

			ImGui::InputText("Path", model_path, IM_ARRAYSIZE(model_path));
			ImGui::SameLine();
			if (ImGui::Button("..."))
			{
				importAssetsPath = Files::GetInstance().GetAssetsPath() / "Models";
				filePath = &importAssetsPath;
				//showFileBrowser = true;
				FileExplorer(window_p, filePath);
			}
			if (ImGui::Button("Cancel"))
			{
				showImportModelPanel = false;
				strcpy_s(model_path, importAssetsPath.string().c_str());
			}
			ImGui::SameLine();
			if (ImGui::Button("Confirm"))
			{
				std::string path_s = model_path;
				Model* new_model = new Model(std::filesystem::path(path_s));
				if (new_model->meshes.size() == 0)
				{
					info = "Load failed";
				}
				else
				{
					showImportModelPanel = false;
					strcpy_s(model_path, importAssetsPath.string().c_str());
				}
			}
			ImGui::Text(info.c_str());
			ImGui::End();
		}
	}

	void UI::ImportShaderPanel(MainWindow* window_p)
	{
		if (!showImportShaderPanel)
		{
			return;
		}
		int32 width = 500;
		int32 height = 200;
		ImGui::SetNextWindowPos(ImVec2((float32) ((window_p->width - width) / 2), (float32) ((window_p->height - height) / 2)), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
		{
			ImGui::Begin("Import Shader");

			static std::string info = "";

			static char vertex_path [128] = "vertex path..";
			ImGui::InputText("vertex Path", vertex_path, IM_ARRAYSIZE(vertex_path));

			static char frag_path [128] = "frag path..";
			ImGui::InputText("frag Path", frag_path, IM_ARRAYSIZE(frag_path));

			if (ImGui::Button("Cancel"))
			{
				showImportShaderPanel = false;
				strcpy_s(vertex_path, "vertex path..");
				strcpy_s(frag_path, "frag path..");
			}
			ImGui::SameLine();
			if (ImGui::Button("Confirm"))
			{
				std::string vert_path_s = vertex_path;
				std::string frag_path_s = frag_path;
				Shader* new_shader = new Shader(vert_path_s.c_str(), frag_path_s.c_str());
				if (new_shader == nullptr)
				{
					info = "Load failed";
				}
				else
				{
					showImportShaderPanel = false;
					strcpy_s(vertex_path, "vert path..");
					strcpy_s(frag_path, "frag path..");
				}
			}
			ImGui::Text(info.c_str());
			ImGui::End();
		}
	}

	void UI::ImportTexturePanel(MainWindow* window_p)
	{
		if (!showImportTexturePanel)
		{
			return;
		}
		int32 width = 500;
		int32 height = 200;
		ImGui::SetNextWindowPos(ImVec2((float32) ((window_p->width - width) / 2), (float32) ((window_p->height - height) / 2)), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Appearing);
		ImGui::Begin("Import Texture");
		static char tex_path [128];
		strcpy_s(tex_path, importAssetsPath.string().c_str());
		static std::string info = "";
		ImGui::InputText("Texture Path", tex_path, IM_ARRAYSIZE(tex_path));
		ImGui::SameLine();
		if (ImGui::Button("..."))
		{
			importAssetsPath = Files::GetInstance().GetAssetsPath() / "Textures";
			filePath = &importAssetsPath;
			//showFileBrowser = true;
			FileExplorer(window_p, filePath);
		}
		if (ImGui::Button("Cancel"))
		{
			showImportTexturePanel = false;
			strcpy_s(tex_path, importAssetsPath.string().c_str());
		}
		ImGui::SameLine();
		if (ImGui::Button("Confirm"))
		{
			std::string path_s = tex_path;
			Texture* new_tex = new Texture(path_s.c_str());
			if (new_tex == nullptr)
			{
				info = "Load failed";
			}
			else
			{
				showImportTexturePanel = false;
				strcpy_s(tex_path, importAssetsPath.string().c_str());
			}
		}
		ImGui::Text(info.c_str());
		ImGui::End();
	}

	void UI::FileBrowser(MainWindow* window_p, std::filesystem::path* path_p)
	{
		try
		{
			if (!showFileBrowser)
			{
				return;
			}
			int32 width = 500;
			int32 height = 300;
			ImGui::SetNextWindowPos(ImVec2((float32) ((window_p->width - width) / 2), (float32) ((window_p->height - height) / 2)), ImGuiCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2((float32) width, (float32) height), ImGuiCond_Appearing);

			ImGui::Begin("File Browser");
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

			if (ImGui::Button(".."))
			{
				*path_p = path_p->parent_path();
			}
			ImGui::SameLine();
			std::vector<fs::path> roots = Files::GetInstance().GetRootPaths();
			int32 rootNum = (int32) roots.size();
			static int32 rootIndex = 0;
			if (ImGui::BeginCombo("root paths", path_p->string().c_str()))
			{
				for (int32 n = 0; n < rootNum; n++)
				{
					const bool isSelected = (rootIndex == n);
					if (ImGui::Selectable(roots [n].string().c_str(), isSelected))
					{
						rootIndex = n;
						*path_p = fs::path(roots [n].string().c_str());
					}
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			std::vector<fs::directory_entry> files;
			for (auto const& dir_entry : fs::directory_iterator { *path_p })
			{
				files.push_back(dir_entry);
			}
			ImGuiWindowFlags windowFlags = ImGuiWindowFlags_HorizontalScrollbar;
			ImGui::BeginChild("FileList", ImVec2((float32) (width - 50), (float32) (height - 100)), ImGuiChildFlags_Border, windowFlags);
			static int32 selectedFile = -1;
			for (uint32 i = 0; i < files.size(); i++)
			{
				std::string fileName = files [i].path().filename().string();
				float32 witdh = 16;
				float32 height = 16;
				ImVec2 uvMin = ImVec2(0.0f, 0.0f);
				ImVec2 uvMax = ImVec2(1.0f, 1.0f);
				ImVec4 tintCol = ImGui::GetStyleColorVec4(ImGuiCol_Text);
				/*if (fs::is_directory(files [i]))
				{
				}
				else
				{
				}
				ImGui::SameLine();*/
				if (ImGui::Selectable(fileName.c_str(), selectedFile == i))
				{
					if (selectedFile == i)
					{
						if (fs::is_directory(files [selectedFile]))
						{
							*path_p = files [selectedFile].path();
						}
						else
						{
							*path_p = files [selectedFile].path();
							showFileBrowser = false;
						}
						selectedFile = -1;
					}
					else
					{
						selectedFile = i;
					}
				}
			}
			ImGui::EndChild();
			if (ImGui::Button("Cancel"))
			{
				showFileBrowser = false;
			}
			ImGui::SameLine();
			if (ImGui::Button("Confirm"))
			{
				if (selectedFile != -1)
				{
					if (fs::is_directory(files [selectedFile]))
					{
						*path_p = files [selectedFile].path();
					}
					else
					{
						*path_p = files [selectedFile].path();
						showFileBrowser = false;
					}
					selectedFile = -1;
				}
				else
				{
					showFileBrowser = false;
				}
			}
			ImGui::PopStyleVar();
			ImGui::End();
		}
		catch (const std::filesystem::filesystem_error& ex)
		{
			std::cerr << "Filesystem error: " << ex.what() << std::endl;
		}

	}

	void UI::FileExplorer(MainWindow* window_p, std::filesystem::path* path_p)
	{
		try
		{
			OPENFILENAME ofn;
			TCHAR szFile [260] = { 0 };

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFile = szFile;
			ofn.lpstrFile [0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = TEXT("ALL Files\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileName(&ofn) == TRUE)
			{
				std::filesystem::path filePath(ofn.lpstrFile);
				*path_p = filePath;
			}
		}
		catch (const std::filesystem::filesystem_error& ex)
		{
			std::cerr << "Filesystem error: " << ex.what() << std::endl;
		}
	}
}

/*
Menu
file edit assets object component windows help
*/
/*
Panel

hierarchy panel
scene panel
inspector panel
project panel
console panel
game panel
*/
/*
+---------+--------------------+----------+
|         |                    |          |
|         |                    |          |
|hierarchy|       scene        | inspector|
|         |                    |          |
|         |                    |          |
+---------+--------------------+----------+
|       project/console        |   game   |
+------------------------------+----------+
*/
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