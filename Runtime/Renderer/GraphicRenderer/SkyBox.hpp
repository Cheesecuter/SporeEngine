#pragma once
#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <Types.hpp>
#include <Shader.hpp>
#include <Camera.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	class SkyBox
	{
	public:
		SkyBox();
		~SkyBox();
		void Draw(Camera* p_camera, mat4x4f p_projection, mat4x4f p_view);

	protected:

	private:
		uint32 m_VAO, m_VBO;
		Shader* m_shader;
		uint32 m_cubemap_texture;
		std::vector<std::string> m_faces {
			"./Assets/Textures/sky/right1.jpg",
			"./Assets/Textures/sky/left1.jpg",
			"./Assets/Textures/sky/top1.jpg",
			"./Assets/Textures/sky/bottom1.jpg",
			"./Assets/Textures/sky/front1.jpg",
			"./Assets/Textures/sky/back1.jpg",
		};
		const float32 m_vertices [108] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		void Init();
		uint32 LoadCubeMap();
	};
}

#endif
