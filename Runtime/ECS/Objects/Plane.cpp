#include <Plane.hpp>

namespace Spore
{
	Plane::Plane(const std::string& identifier_p) : Object(identifier_p)
	{
		Init();
	}

	Plane::~Plane()
	{

	}

	void Plane::Init()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) (3 * sizeof(float32)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float32), (void*) (6 * sizeof(float32)));
		glBindVertexArray(0);
	}

	void Plane::Render(Shader* shader_p)
	{
		mat4x4f model = mat4x4f(1.0f);
		shader_p->SetMat4("model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}