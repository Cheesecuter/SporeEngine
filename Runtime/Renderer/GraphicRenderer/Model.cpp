#include <Model.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	Model::Model(std::string const& path, bool gamma) : gammaCorrection(gamma)
	{
		LoadModel(path);
	}

	Model::Model(std::filesystem::path path, bool gamma) : gammaCorrection(gamma)
	{
		LoadModel(path.string().c_str());
	}

	Model::~Model()
	{
		DeleteModel();
	}

	void Model::Draw(Shader& shader)
	{
		for (uint32 i = 0; i < meshes.size(); i++)
			meshes [i].Draw(shader);
	}

	void Model::LoadModel(std::string const& path)
	{
		// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors (if is Not Zero)
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		// retrieve the directory path of the filepath
		std::string pathS = path;
		std::replace(pathS.begin(), pathS.end(), '\\', '/');
		directory = pathS.substr(0, pathS.find_last_of('/'));
		identifier = pathS.substr(pathS.find_last_of('/') + 1, pathS.size());
		// process ASSIMP's root node recursively
		ProcessNode(scene->mRootNode, scene);
		AssetsManager::GetInstance().modelMapper.insert(std::make_pair(identifier, this));
		AssetsManager::GetInstance().modelCounter [identifier] = 0;
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// process each mesh located at the current node
		for (uint32 i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene
			// the scene contains all the data, node is just to keep stuff organized (like relation between nodes)
			aiMesh* mesh = scene->mMeshes [node->mMeshes [i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (uint32 i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren [i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		// data to fill
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Texture> textures;

		// walk through each of the mesh's vertices
		for (uint32 i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vec3f vector;
			// position
			vector.x = mesh->mVertices [i].x;
			vector.y = mesh->mVertices [i].y;
			vector.z = mesh->mVertices [i].z;
			vertex.Position = vector;
			// normals
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals [i].x;
				vector.y = mesh->mNormals [i].y;
				vector.z = mesh->mNormals [i].z;
				vertex.Normal = vector;
			}
			// texture coordinates
			if (mesh->mTextureCoords [0])
			{
				vec2f vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the  assumption that we won't
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords [0][i].x;
				vec.y = mesh->mTextureCoords [0][i].y;
				vertex.TexCoords = vec;
				// tangent
				vector.x = mesh->mTangents [i].x;
				vector.y = mesh->mTangents [i].y;
				vector.z = mesh->mTangents [i].z;
				vertex.Tangent = vector;
				// bitangent
				vector.x = mesh->mBitangents [i].x;
				vector.y = mesh->mBitangents [i].y;
				vector.z = mesh->mBitangents [i].z;
				vertex.Bitangent = vector;
			}
			else
			{
				vertex.TexCoords = vec2f(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}
		// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices
		for (uint32 i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces [i];
			// retrieve all indices of the face and store them in the indices vector
			for (uint32 j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices [j]);
		}
		// process materials
		aiMaterial* material = scene->mMaterials [mesh->mMaterialIndex];
		// we assume a convertion for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		//// 1. diffuse maps
		//std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//// 2. specular maps
		//std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		//// 3. normal maps
		//std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		////std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		//// 4. height maps
		//std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		////std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


		// 1. ambient maps
		std::vector<Texture> ambientMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_ambient");
		textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
		// 2. ambient occlusion maps
		std::vector<Texture> ambientOcclusionMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, "texture_ambient_occlusion");
		textures.insert(textures.end(), ambientOcclusionMaps.begin(), ambientOcclusionMaps.end());
		// 3. base color maps
		std::vector<Texture> baseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "texture_base_color");
		textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
		// 4. clear coat maps
		std::vector<Texture> clearCoatMaps = LoadMaterialTextures(material, aiTextureType_CLEARCOAT, "texture_clear_coat");
		textures.insert(textures.end(), clearCoatMaps.begin(), clearCoatMaps.end());
		// 5. diffuse maps
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 6. diffuse roughness maps
		std::vector<Texture> diffuseRoughnessMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "texture_diffuse_roughness");
		textures.insert(textures.end(), diffuseRoughnessMaps.begin(), diffuseRoughnessMaps.end());
		// 7. displacement maps
		std::vector<Texture> displacementMaps = LoadMaterialTextures(material, aiTextureType_DISPLACEMENT, "texture_displacement");
		textures.insert(textures.end(), displacementMaps.begin(), displacementMaps.end());
		// 8. emission color maps
		std::vector<Texture> emissionColorMaps = LoadMaterialTextures(material, aiTextureType_EMISSION_COLOR, "texture_emission_color");
		textures.insert(textures.end(), emissionColorMaps.begin(), emissionColorMaps.end());
		// 9. emissive maps
		std::vector<Texture> emissiveMaps = LoadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emissive");
		textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
		// 10. height maps
		std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		// 11. lightmap maps
		std::vector<Texture> lightmapMaps = LoadMaterialTextures(material, aiTextureType_LIGHTMAP, "texture_lightmap");
		textures.insert(textures.end(), lightmapMaps.begin(), lightmapMaps.end());
		// 12. metalness maps
		std::vector<Texture> metalnessMaps = LoadMaterialTextures(material, aiTextureType_METALNESS, "texture_metalness");
		textures.insert(textures.end(), metalnessMaps.begin(), metalnessMaps.end());
		// 13. normal maps
		std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 14. normal camera maps
		std::vector<Texture> normalCameraMaps = LoadMaterialTextures(material, aiTextureType_NORMAL_CAMERA, "texture_normal_camera");
		textures.insert(textures.end(), normalCameraMaps.begin(), normalCameraMaps.end());
		// 15. opacity maps
		std::vector<Texture> opacityMaps = LoadMaterialTextures(material, aiTextureType_OPACITY, "texture_opacity");
		textures.insert(textures.end(), opacityMaps.begin(), opacityMaps.end());
		// 16. reflection maps
		std::vector<Texture> reflectionMaps = LoadMaterialTextures(material, aiTextureType_REFLECTION, "texture_reflection");
		textures.insert(textures.end(), reflectionMaps.begin(), reflectionMaps.end());
		// 17. sheen maps
		std::vector<Texture> sheenMaps = LoadMaterialTextures(material, aiTextureType_SHEEN, "texture_sheen");
		textures.insert(textures.end(), sheenMaps.begin(), sheenMaps.end());
		// 18. shininess maps
		std::vector<Texture> shininessMaps = LoadMaterialTextures(material, aiTextureType_SHININESS, "texture_shininess");
		textures.insert(textures.end(), shininessMaps.begin(), shininessMaps.end());
		// 19. specular maps
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 20. transmission maps
		std::vector<Texture> transmissionMaps = LoadMaterialTextures(material, aiTextureType_TRANSMISSION, "texture_transmission");
		textures.insert(textures.end(), transmissionMaps.begin(), transmissionMaps.end());

		if (textures.size() == 0)
		{
			Texture texture;
			std::string path = "default.png";
			texture.ID = TextureFromFile(path.c_str(), this->directory);
			texture.type = "texture_default";
			texture.path = path.c_str();
			textures.insert(textures.end(), texture);
		}

		// return a mesh object created from the extracted mesh data
		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;
		for (uint32 i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			for (uint32 j = 0; j < texturesLoaded.size(); j++)
			{
				if (std::strcmp(texturesLoaded [j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(texturesLoaded [j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				// if texture hasn't been loaded already, load it
				Texture texture;
				texture.ID = TextureFromFile(str.C_Str(), this->directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				// store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures
				texturesLoaded.push_back(texture);
			}
		}
		return textures;
	}

	uint32 TextureFromFile(const char* path, const std::string& directory, bool gamma)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;

		uint32 textureID;
		glGenTextures(1, &textureID);

		int32 width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format = GL_RED;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "SporeEngine::Model: Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}

	void Model::AddObserver(std::shared_ptr<ModelObserver> observer_p)
	{
		observerList.push_back(observer_p);
	}

	void Model::RemoveObserver(std::shared_ptr<ModelObserver> observer_p)
	{
		const std::vector<std::shared_ptr<ModelObserver>>::iterator it = std::find(observerList.begin(), observerList.end(), observer_p);
		if (it != observerList.end())
		{
			observerList.erase(it);
		}
	}

	void Model::DeleteModel()
	{
		for (std::shared_ptr<ModelObserver> observer : observerList)
		{
			observer->OnModelDeleted(this);
		}
	}
}