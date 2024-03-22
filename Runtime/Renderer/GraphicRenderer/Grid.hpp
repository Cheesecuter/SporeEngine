#pragma once
#ifndef GRID_HPP
#define GRID_HPP

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
		void Draw(Shader* shader_p);

	protected:

	private:
		uint32 quadVAO, quadVBO;
		const float32 quadVertices [24] = {
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

#endif
