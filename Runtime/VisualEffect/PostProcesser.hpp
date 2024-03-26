#pragma once
#ifndef POST_PROCESSER_HPP
#define POST_PROCESSER_HPP

#include <Types.hpp>
#include <PostProcess.hpp>

namespace Spore
{
	class PostProcesser
	{
	public:
		PostProcesser(uint32 screenWidth_p, uint32 screenHeight_p);
		~PostProcesser();

		void SetPostProcess(PostProcess* postProcess_p);
		PostProcess* GetPostProcesS();
		void Render(mat4f projection_p, mat4f view_p, mat4f model_p);

	protected:

	private:
		uint32 FBO, quadVAO, quadVBO;
		uint32 texture;
		uint32 depthBuffer;
		PostProcess* postProcess;
		float quadVertices [24] = { 
		// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
		};
	};
}

#endif
