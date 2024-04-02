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
		UI(MainWindow* p_window);
		~UI();
		void InitImGui(MainWindow* p_window);
		void UITerminate();
		void RenderPanels(MainWindow* p_window);
		void ShowDemoWindow();
		void FileBrowser(MainWindow* p_window, std::filesystem::path* p_path);
		void FileExplorer(MainWindow* p_window, std::filesystem::path* p_path);
		void ImportShaderPanel(MainWindow* p_window);
		void ImportTexturePanel(MainWindow* p_window);
		void ImportModelPanel(MainWindow* p_window);

	protected:

	private:
		bool m_show_import_model_panel = false;
		bool m_show_import_shader_panel = false;
		bool m_show_import_texture_panel = false;
		bool m_show_file_browser = false;
		bool m_show_console = false;
		bool m_show_demo_window = false;
		bool m_show_another_window = false;
		std::filesystem::path m_file_path;
		std::filesystem::path m_import_assets_path = Files::GetInstance().GetAssetsPath();
		MainWindow* m_window;
		std::string m_selected_scene_identifier = "";
		Scene* m_selected_scene;
		std::string m_selected_object_identifier = "";
		Object* m_selected_object;
		std::unordered_map<std::string, PostProcess*> m_post_process_mapper;
		Texture* m_button_image_reset;

		void InitImages();
		void RenderMenuBar(MainWindow* p_window);
		void RenderHierarchyPanel(MainWindow* p_window);
		void RenderScenePanel(MainWindow* p_window);
		void RenderInspectorPanel(MainWindow* p_window);
		void RenderProjectPanel(MainWindow* p_window);
		void RenderConsolePanel(MainWindow* p_window);
	};
}

#endif
