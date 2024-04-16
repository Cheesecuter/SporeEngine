#pragma once

#include <Types.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>
#include <Files.hpp>
#include <ModelObserver.hpp>

namespace Spore
{
	uint32 TextureFromFile(const char* p_path, const std::string& p_directory, bool p_gamma = false);

	class Model
	{
	public:
		Model(const char* p_path, bool p_gamma = false);
		Model(std::filesystem::path p_path, bool p_gamma = false);
		~Model();

		std::string m_identifier;
		std::vector<Texture> m_textures_loaded;
		std::vector<Mesh> m_meshes;
		std::string m_directory;
		bool m_gamma_correction;

		void AddObserver(ModelObserver* p_observer);
		void RemoveObserver(ModelObserver* p_observer);
		void DeleteModel();
		void Draw(Shader& p_shader);

	protected:

	private:
		std::vector<ModelObserver*> m_observer_list;

		void LoadAsset(const char* p_path);
		void ProcessNode(aiNode* p_node, const aiScene* p_scene);
		Mesh ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* p_material, aiTextureType p_type, std::string p_type_name);
	};
}
