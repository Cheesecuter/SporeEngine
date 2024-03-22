#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <Types.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

#define MAX_BONE_INFLUENCE 4

namespace Spore
{
	struct Vertex
	{
		vec3f Position;
		vec3f Normal;
		vec2f TexCoords;
		vec3f Tangent;
		vec3f Bitangent;
		// bone indexes which will influence this vertex
		int16 m_BoneIDs [MAX_BONE_INFLUENCE] = {};
		// weights from each bone
		float32 m_Weights [MAX_BONE_INFLUENCE] = {};
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices_p, std::vector<uint32> indices_p, std::vector<Texture> textures_p);
		
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Texture> textures;
		uint32 VAO;

		void Draw(Shader& shader_p);

	private:
		// render data
		uint32 VBO, EBO;

		// initializes all the buffer objects/arrays
		void SetupMesh();
	};
}

#endif
