#include <Grid.hpp>

namespace Spore
{
	Grid::Grid()
	{
		Init();
	}

	Grid::~Grid()
	{
		glDeleteVertexArrays(1, &m_quad_VAO);
		glDeleteBuffers(1, &m_quad_VBO);
	}

	void Grid::Init()
	{
		glGenVertexArrays(1, &m_quad_VAO);
		glGenBuffers(1, &m_quad_VBO);
		glBindVertexArray(m_quad_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_quad_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_quad_vertices), &m_quad_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float32), (void*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float32), (void*) (2 * sizeof(float32)));
	}

	void Grid::Draw(Shader* p_shader)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		p_shader->Use();
		glBindVertexArray(m_quad_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glDisable(GL_BLEND);
	}
}