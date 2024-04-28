#pragma once

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
			"./Assets/Utils/Textures/Skybox/right.jpg",
			"./Assets/Utils/Textures/Skybox/left.jpg",
			"./Assets/Utils/Textures/Skybox/top.jpg",
			"./Assets/Utils/Textures/Skybox/bottom.jpg",
			"./Assets/Utils/Textures/Skybox/front.jpg",
			"./Assets/Utils/Textures/Skybox/back.jpg",
		};
		const float32 m_vertices [108] = {
			// positions          
			-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f
		};

		void Init();
		uint32 LoadCubeMap();
	};
}
