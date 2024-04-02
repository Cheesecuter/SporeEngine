#pragma once
#ifndef RENDERPIPELINE_HPP
#define RENDERPIPELINE_HPP

#include <Types.hpp>
#include <Scene.hpp>
#include <Grid.hpp>
#include <SkyBox.hpp>
#include <Light.hpp>
#include <Plane.hpp>
#include <PostProcesser.hpp>
#include <PostProcess.hpp>

namespace Spore
{
	class RenderPipeline
	{
	public:
		RenderPipeline();
		~RenderPipeline();

		std::map<std::string, Scene*> sceneMapper;
		bool skyboxOn = true;
		bool gammaCorrection = false;
		bool shadowMapOn = false;
		bool postProcessOn = true;
		std::string postProcess = "";

		void Initialize();
		void AddScene(Scene* scene_p);
		void DeleteScene(Scene* scene_p);
		void DeleteScene(std::string identifier_p);
		void SetScenePos(uint32 sceneX_p, uint32 sceneY_p);
		vec2f GetScenePos();
		void SetSceneSize(uint32 sceneWidth_p, uint32 sceneHeight_p);
		vec2f GetSceneSize();
		void UpdateSceneFBO();
		void UpdateSceneRBO();
		void PreRender();
		void Render(std::vector<Shader*> shaders_p, Camera* camera_p,
					uint32 scrWidth_p, uint32 scrHeight_p,
					mat4f projection_p, mat4f view_p, mat4f model_p);
		void ForwardRender(std::vector<Shader*> shaders_p, Camera* camera_p,
						   uint32 scrWidth_p, uint32 scrHeight_p,
						   mat4f projection_p, mat4f view_p, mat4f model_p);
		void InitGBuffer(uint32 scrWidth_p, uint32 scrHeight_p);
		void DeferredRender(std::vector<Shader*> shaders_p, Camera* camera_p,
							uint32 scrWidth_p, uint32 scrHeight_p,
							mat4f projection_p, mat4f view_p, mat4f model_p);
		void InitPostProcesser(uint32 screenWidth_p, uint32 screenHeight_p, PostProcess* postProcess_p);
		PostProcesser* GetPostProcesser();
		void PostProcessRenderToFBO();
		void PostProcessFBO();
		void InitShadowMap();
		void ShadowMapRender(std::shared_ptr<Light> light_p,
							 std::vector<Shader*> shaders_p, Camera* camera_p,
							 uint32 scrWidth_p, uint32 scrHeight_p,
							 mat4f projection_p, mat4f view_p, mat4f model_p);
		void ShadingRender();
		void InitGrid();
		void RenderGrid(Camera* camera_p, mat4f projection_p, mat4f view_p);
		void InitSkyBox();
		void RenderSkyBox(Camera* camera_p, mat4f projection_p, mat4f view_p);

	protected:

	private:
		bool initialized;
		uint32 gBuffer;
		uint32 gPosition, gNormal, gAlbedoSpec;
		uint32 forwardRenderFBO;
		uint32 attachments [3];
		uint32 rboDepth;
		PostProcesser* postProcesser;
		SkyBox* skybox;
		Grid* grid;
		const uint32 SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
		uint32 sceneX, sceneY;
		uint32 sceneWidth, sceneHeight;
		Shader* shadowMappingShader;
		Shader* shadowMappingDepthShader;
		Shader* debugDepthQuadShader;
		uint32 depthMap, depthMapFBO;
		float32 nearPlane = 1.0f, farPlane = 100.0f;
		mat4x4f lightProjection, lightView, lightSpaceMatrix;
	};
}

#endif
