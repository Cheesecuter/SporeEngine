#pragma once
#ifndef PLANE_HPP
#define PLANE_HPP

#include <Types.hpp>
#include <Texture.hpp>
#include <Object.hpp>

namespace Spore
{
	class Plane : public Object
	{
	public:
		Plane(const std::string& identifier_p);
		~Plane();
		void Render(std::vector<Shader*> shaders_p, Texture* texture_p, mat4x4f model_p);

	protected:

	private:
		uint32 VAO, VBO;
		std::map<std::string, Model*> modelMapper;
		float vertices [48] = {
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

#endif
