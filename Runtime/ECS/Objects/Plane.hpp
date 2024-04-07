#pragma once

#include <Types.hpp>
#include <Texture.hpp>
#include <Object.hpp>

namespace Spore
{
	class Plane : public Object
	{
	public:
		Plane(const std::string& p_identifier);
		~Plane();
		void Render(std::vector<Shader*> p_shaders, Texture* p_texture, mat4x4f p_model);

	protected:

	private:
		uint32 m_VAO, m_VBO;
		std::map<std::string, Model*> m_model_mapper;
		float m_vertices [48] = {
			// positions            // normals         // texcoords
			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
			 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
		};

		void Init();
	};
}
