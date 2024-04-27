#pragma once

#include <Types.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

#define MAX_BONE_INFLUENCE 4

namespace Spore
{
	struct Vertex
	{
		vec3f m_position;
		vec3f m_normal;
		vec2f m_tex_coords;
		vec3f m_tangent;
		vec3f m_bitangent;
		// bone indexes which will influence this vertex
		int16 m_bone_IDs [MAX_BONE_INFLUENCE] = {};
		// weights from each bone
		float32 m_weights [MAX_BONE_INFLUENCE] = {};
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> p_vertices, std::vector<uint32> p_indices, std::vector<Texture*> p_textures);
		
		std::vector<Vertex> m_vertices;
		std::vector<uint32> m_indices;
		std::vector<Texture*> m_textures;
		uint32 m_VAO;

		void Draw(Shader& p_shader);

	private:
		uint32 m_VBO, m_EBO;

		void SetupMesh();
	};
}
