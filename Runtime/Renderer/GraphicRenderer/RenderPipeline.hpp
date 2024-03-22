#pragma once
#ifndef RENDERPIPELINE_HPP
#define RENDERPIPELINE_HPP

#include <Types.hpp>
#include <Scene.hpp>
#include <Grid.hpp>
#include <SkyBox.hpp>

namespace Spore
{
	class RenderPipeline
	{
	public:
		RenderPipeline();
		~RenderPipeline();

		std::map<std::string, std::shared_ptr<Scene>> sceneMapper;
		bool skyboxOn = true;
		bool gammaCorrection = true;

		void Initialize();
		void AddScene(std::shared_ptr<Scene> scene_p);
		void DeleteScene(std::shared_ptr<Scene> scene_p);
		void DeleteScene(std::string identifier_p);
		void PreRender();
		void Render(std::vector<Shader> shaders_p, Camera* camera_p,
					uint32 scrWidth_p, uint32 scrHeight_p,
					mat4f projection_p, mat4f view_p, mat4f model_p);
		void ForwardRender(std::vector<Shader> shaders_p, Camera* camera_p,
						   uint32 scrWidth_p, uint32 scrHeight_p,
						   mat4f projection_p, mat4f view_p, mat4f model_p);
		void InitGBuffer(uint32 scrWidth_p, uint32 scrHeight_p);
		void DeferredRender(std::vector<Shader> shaders_p, Camera* camera_p,
							uint32 scrWidth_p, uint32 scrHeight_p,
							mat4f projection_p, mat4f view_p, mat4f model_p);
		void PostProcessing();
		void RenderGrid(Camera* camera_p, mat4f projection_p, mat4f view_p);
		void InitSkyBox();
		void RenderSkyBox(Camera* camera_p, mat4f projection_p, mat4f view_p);

	protected:

	private:
		bool initialized;
		uint32 gBuffer;
		uint32 gPosition, gNormal, gAlbedoSpec;
		uint32 attachments [3];
		uint32 rboDepth;
		SkyBox skybox;
	};
}

#endif
