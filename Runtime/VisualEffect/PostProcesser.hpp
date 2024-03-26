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
		void Render();

	protected:

	private:
		uint32 FBO;
		uint32 texture;
		uint32 depthBuffer;
		PostProcess* postProcess;
	};
}

#endif
