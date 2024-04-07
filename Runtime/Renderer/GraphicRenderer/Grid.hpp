#pragma once

#include <Types.hpp>
#include <Shader.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	class Grid
	{
	public:
		Grid();
		~Grid();
		void Draw(Shader* p_shader);

	protected:

	private:
		uint32 m_quad_VAO, m_quad_VBO;
		const float32 m_quad_vertices [24] = {
			// positions	// texCoords
			-1.0f,  1.0f,	0.0f, 1.0f,
			-1.0f, -1.0f,	0.0f, 0.0f,
			1.0f, -1.0f,	1.0f, 0.0f,
			-1.0f,  1.0f,	0.0f, 1.0f,
			1.0f, -1.0f,	1.0f, 0.0f,
			1.0f,  1.0f,	1.0f, 1.0f
		};

		void Init();
	};
}
