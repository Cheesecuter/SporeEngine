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
		PostProcesser(uint32 sceneWidth_p, uint32 sceneHeight_p, PostProcess* postProcess_p);
		~PostProcesser();

		void SetPostProcess(std::string identifier_p);
		void AddPostProcess(PostProcess* postProcess_p);
		PostProcess* GetPostProcess();
		uint32 GetFrameBufferTexture();
		uint32 GetDepthBuffer();
		void RenderToFBO();
		void RenderFBO();

	protected:

	private:
		uint32 FBO, quadVAO, quadVBO;
		uint32 texture;
		uint32 depthBuffer;
		PostProcess* postProcess;
		std::unordered_map<std::string, PostProcess*> postProcessMapper;
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
