#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

#include <Types.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>

namespace Spore
{
	uint32 TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

	class Model;

	class ModelObserver
	{
	public:
		virtual ~ModelObserver()
		{
		};
		virtual void OnModelDeleted(Model* model_p) = 0;
	};

	class Model
	{
	public:
		Model(std::string const& path, bool gamma = false);
		Model(std::filesystem::path path, bool gamma = false);
		~Model();

		std::string identifier;
		std::vector<Texture> texturesLoaded;
		std::vector<Mesh> meshes;
		std::string directory;
		bool gammaCorrection;

		void AddObserver(std::shared_ptr<ModelObserver> observer_p);
		void RemoveObserver(std::shared_ptr<ModelObserver> observer_p);
		void DeleteModel();
		void Draw(Shader& shader);

	private:
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		std::vector<std::shared_ptr<ModelObserver>> observerList;
		void LoadModel(std::string const& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
	};
}

#endif

