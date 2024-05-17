#include <Model.hpp>
#include <AssetsManager.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	Model::Model(const char* p_path, bool p_gamma) : m_gamma_correction(p_gamma)
	{
		LoadAsset(p_path);
	}

	Model::Model(std::filesystem::path p_path, bool p_gamma) : m_gamma_correction(p_gamma)
	{
		LoadAsset(p_path.string().c_str());
	}

	Model::~Model()
	{
		DeleteModel();
	}

	void Model::AddObserver(ModelObserver* p_observer)
	{
		m_observer_list.push_back(p_observer);
	}

	void Model::RemoveObserver(ModelObserver* p_observer)
	{
		const std::vector<ModelObserver*>::iterator it = std::find(m_observer_list.begin(), m_observer_list.end(), p_observer);
		if (it != m_observer_list.end())
		{
			m_observer_list.erase(it);
		}
	}

	void Model::DeleteModel()
	{
		for (ModelObserver* observer : m_observer_list)
		{
			observer->OnModelDeleted(this);
		}
	}

	void Model::Draw(Shader& p_shader)
	{
		for (uint32 i = 0; i < m_meshes.size(); i++)
			m_meshes [i]->Draw(p_shader);
	}

	std::vector<Mesh*> Model::GetMeshes()
	{
		return m_meshes;
	}

	void Model::LoadAsset(const char* p_path)
	{
		// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(p_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors (if is Not Zero)
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ConsoleLogger::GetInstance().Logger()->error("Model::LoadAsset: Assimp: {}", importer.GetErrorString());
			return;
		}
		// retrieve the directory path of the filepath
		std::string pathS = p_path;
		std::replace(pathS.begin(), pathS.end(), '\\', '/');
		m_directory = pathS.substr(0, pathS.find_last_of('/'));
		m_identifier = pathS.substr(pathS.find_last_of('/') + 1, pathS.size());
		m_path = pathS;
		// process ASSIMP's root node recursively
		ProcessNode(scene->mRootNode, scene);
		AssetsManager::GetInstance().m_model_mapper.insert(std::make_pair(m_identifier, this));
	}

	void Model::ProcessNode(aiNode* p_node, const aiScene* p_scene)
	{
		// process each mesh located at the current node
		for (uint32 i = 0; i < p_node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene
			// the scene contains all the data, node is just to keep stuff organized (like relation between nodes)
			aiMesh* mesh = p_scene->mMeshes [p_node->mMeshes [i]];
			m_meshes.push_back(ProcessMesh(mesh, p_scene));
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (uint32 i = 0; i < p_node->mNumChildren; i++)
		{
			ProcessNode(p_node->mChildren [i], p_scene);
		}
	}

	Mesh* Model::ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene)
	{
		// data to fill
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Texture*> textures;

		// walk through each of the mesh's vertices
		for (uint32 i = 0; i < p_mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vec3f vector;
			// position
			vector.x = p_mesh->mVertices [i].x;
			vector.y = p_mesh->mVertices [i].y;
			vector.z = p_mesh->mVertices [i].z;
			vertex.m_position = vector;
			// normals
			if (p_mesh->HasNormals())
			{
				vector.x = p_mesh->mNormals [i].x;
				vector.y = p_mesh->mNormals [i].y;
				vector.z = p_mesh->mNormals [i].z;
				vertex.m_normal = vector;
			}
			// texture coordinates
			if (p_mesh->mTextureCoords [0])
			{
				vec2f vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the  assumption that we won't
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = p_mesh->mTextureCoords [0][i].x;
				vec.y = p_mesh->mTextureCoords [0][i].y;
				vertex.m_tex_coords = vec;
				// tangent
				vector.x = p_mesh->mTangents [i].x;
				vector.y = p_mesh->mTangents [i].y;
				vector.z = p_mesh->mTangents [i].z;
				vertex.m_tangent = vector;
				// bitangent
				vector.x = p_mesh->mBitangents [i].x;
				vector.y = p_mesh->mBitangents [i].y;
				vector.z = p_mesh->mBitangents [i].z;
				vertex.m_bitangent = vector;
			}
			else
			{
				vertex.m_tex_coords = vec2f(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}
		// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices
		for (uint32 i = 0; i < p_mesh->mNumFaces; i++)
		{
			aiFace face = p_mesh->mFaces [i];
			// retrieve all indices of the face and store them in the indices vector
			for (uint32 j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices [j]);
		}
		// process materials
		aiMaterial* material = p_scene->mMaterials [p_mesh->mMaterialIndex];
		// we assume a convertion for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		// 1. diffuse maps
		std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		//std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		std::vector<Texture*> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		//std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		std::vector<Texture*> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


		//// 1. ambient maps
		//std::vector<Texture> ambientMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_ambient");
		//textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
		//// 2. ambient occlusion maps
		//std::vector<Texture> ambientOcclusionMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, "texture_ambient_occlusion");
		//textures.insert(textures.end(), ambientOcclusionMaps.begin(), ambientOcclusionMaps.end());
		//// 3. base color maps
		//std::vector<Texture> baseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "texture_base_color");
		//textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
		//// 4. clear coat maps
		//std::vector<Texture> clearCoatMaps = LoadMaterialTextures(material, aiTextureType_CLEARCOAT, "texture_clear_coat");
		//textures.insert(textures.end(), clearCoatMaps.begin(), clearCoatMaps.end());
		//// 5. diffuse maps
		//std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//// 6. diffuse roughness maps
		//std::vector<Texture> diffuseRoughnessMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "texture_diffuse_roughness");
		//textures.insert(textures.end(), diffuseRoughnessMaps.begin(), diffuseRoughnessMaps.end());
		//// 7. displacement maps
		//std::vector<Texture> displacementMaps = LoadMaterialTextures(material, aiTextureType_DISPLACEMENT, "texture_displacement");
		//textures.insert(textures.end(), displacementMaps.begin(), displacementMaps.end());
		//// 8. emission color maps
		//std::vector<Texture> emissionColorMaps = LoadMaterialTextures(material, aiTextureType_EMISSION_COLOR, "texture_emission_color");
		//textures.insert(textures.end(), emissionColorMaps.begin(), emissionColorMaps.end());
		//// 9. emissive maps
		//std::vector<Texture> emissiveMaps = LoadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emissive");
		//textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
		//// 10. height maps
		//std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		//// 11. lightmap maps
		//std::vector<Texture> lightmapMaps = LoadMaterialTextures(material, aiTextureType_LIGHTMAP, "texture_lightmap");
		//textures.insert(textures.end(), lightmapMaps.begin(), lightmapMaps.end());
		//// 12. metalness maps
		//std::vector<Texture> metalnessMaps = LoadMaterialTextures(material, aiTextureType_METALNESS, "texture_metalness");
		//textures.insert(textures.end(), metalnessMaps.begin(), metalnessMaps.end());
		//// 13. normal maps
		//std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		//// 14. normal camera maps
		//std::vector<Texture> normalCameraMaps = LoadMaterialTextures(material, aiTextureType_NORMAL_CAMERA, "texture_normal_camera");
		//textures.insert(textures.end(), normalCameraMaps.begin(), normalCameraMaps.end());
		//// 15. opacity maps
		//std::vector<Texture> opacityMaps = LoadMaterialTextures(material, aiTextureType_OPACITY, "texture_opacity");
		//textures.insert(textures.end(), opacityMaps.begin(), opacityMaps.end());
		//// 16. reflection maps
		//std::vector<Texture> reflectionMaps = LoadMaterialTextures(material, aiTextureType_REFLECTION, "texture_reflection");
		//textures.insert(textures.end(), reflectionMaps.begin(), reflectionMaps.end());
		//// 17. sheen maps
		//std::vector<Texture> sheenMaps = LoadMaterialTextures(material, aiTextureType_SHEEN, "texture_sheen");
		//textures.insert(textures.end(), sheenMaps.begin(), sheenMaps.end());
		//// 18. shininess maps
		//std::vector<Texture> shininessMaps = LoadMaterialTextures(material, aiTextureType_SHININESS, "texture_shininess");
		//textures.insert(textures.end(), shininessMaps.begin(), shininessMaps.end());
		//// 19. specular maps
		//std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		//// 20. transmission maps
		//std::vector<Texture> transmissionMaps = LoadMaterialTextures(material, aiTextureType_TRANSMISSION, "texture_transmission");
		//textures.insert(textures.end(), transmissionMaps.begin(), transmissionMaps.end());

		if (textures.size() == 0)
		{
			Texture* texture = AssetsManager::GetInstance().m_texture_mapper ["default.png"];
			textures.insert(textures.end(), texture);
			m_textures_loaded.push_back(texture);
		}

		// return a mesh object created from the extracted mesh data
		Mesh* mesh = new Mesh(vertices, indices, textures);
		return mesh;
	}

	std::vector<Texture*> Model::LoadMaterialTextures(aiMaterial* p_material, aiTextureType p_type, std::string p_type_name)
	{
		std::vector<Texture*> textures;
		for (uint32 i = 0; i < p_material->GetTextureCount(p_type); i++)
		{
			aiString str;
			p_material->GetTexture(p_type, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			for (uint32 j = 0; j < m_textures_loaded.size(); j++)
			{
				if (std::strcmp(m_textures_loaded [j]->m_path.data(), str.C_Str()) == 0)
				{
					textures.push_back(m_textures_loaded [j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				// if texture hasn't been loaded already, load it
				std::string path = str.C_Str();
				Texture* texture = new Texture(std::string(this->m_directory + "/" + path).c_str());
				textures.push_back(texture);
				// store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures
				m_textures_loaded.push_back(texture);
			}
		}
		return textures;
	}
}