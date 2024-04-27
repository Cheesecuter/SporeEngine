#include <Mesh.hpp>

namespace Spore
{
	Mesh::Mesh(std::vector<Vertex> p_vertices, std::vector<uint32> p_indices, std::vector<Texture*> p_textures) :
		m_vertices(p_vertices), m_indices(p_indices), m_textures(p_textures)
	{
		SetupMesh();
	}

	void Mesh::Draw(Shader& p_shader)
	{
		// bind appropriate textures
		uint32 diffuseNr = 1;
		uint32 specularNr = 1;
		uint32 normalNr = 1;
		uint32 heightNr = 1;
		for (uint32 i = 0; i < m_textures.size(); i++)
		{
			// active proper texture unit before binding
			glActiveTexture(GL_TEXTURE0 + i);
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = m_textures [i]->m_type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);

			// now set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(p_shader.m_ID, (name + number).c_str()), i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, m_textures [i]->m_ID);
		}

		// draw mesh
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, static_cast<uint32>(m_indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// set texture unit back to default
		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::SetupMesh()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to
		// a glm::vec3/2 array which again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices [0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32), &m_indices [0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, m_normal));
		// vertex texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, m_tex_coords));
		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, m_tangent));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, m_bitangent));
		// ids
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*) offsetof(Vertex, m_bone_IDs));
		// weights
		glEnableVertexAttribArray(6);
		glVertexAttribIPointer(6, 4, GL_INT, sizeof(Vertex), (void*) offsetof(Vertex, m_weights));
		glBindVertexArray(0);
	}
}