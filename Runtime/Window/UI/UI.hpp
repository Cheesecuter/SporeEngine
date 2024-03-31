#pragma once
#ifndef UI_HPP
#define UI_HPP

#include <Types.hpp>
#include <Window.hpp>
#include <Files.hpp>
#include <AssetsManager.hpp>
#include <Shader.hpp>
#include <Texture.hpp>
#include <Model.hpp>
#include <Scene.hpp>

namespace Spore
{
	class UIProxy
	{
	public:

	};

	class UI
	{
	public:
		UI(MainWindow* window_p);
		~UI();
		void InitImGui(MainWindow* window_p);
		void UITerminate();
		void RenderPanels(MainWindow* window_p);
		void ShowDemoWindow();
		void FileBrowser(MainWindow* window_p, std::filesystem::path* path_p);
		void FileExplorer(MainWindow* window_p, std::filesystem::path* path_p);
		void ImportShaderPanel(MainWindow* window_p);
		void ImportTexturePanel(MainWindow* window_p);
		void ImportModelPanel(MainWindow* window_p);

	protected:

	private:
		bool showImportModelPanel = false;
		bool showImportShaderPanel = false;
		bool showImportTexturePanel = false;
		bool showFileBrowser = false;
		bool showConsole = false;
		bool show_demo_window = false;
		bool show_another_window = false;
		std::filesystem::path* filePath;
		std::filesystem::path importAssetsPath = Files::GetInstance().GetAssetsPath();
		MainWindow* window;
		int selectedObjectIndex = -1;
		std::shared_ptr<Object> selectedObject;
		std::unordered_map<std::string, PostProcess*> postProcessMapper;
		Texture* btnImgReset;
		void InitImages();
		void RenderMenuBar(MainWindow* window_p);
		void RenderHierarchyPanel(MainWindow* window_p);
		void RenderScenePanel(MainWindow* window_p);
		void RenderInspectorPanel(MainWindow* window_p);
		void RenderProjectPanel(MainWindow* window_p);
		void RenderConsolePanel(MainWindow* window_p);
	};
}

#endif
