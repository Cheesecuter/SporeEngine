#include <RenderPipeline.hpp>

namespace Spore
{
	RenderPipeline::RenderPipeline() : initialized(false)
	{

	}

	RenderPipeline::~RenderPipeline()
	{
	}

	void RenderPipeline::Initialize()
	{
		if (initialized)
		{
			return;
		}

		initialized = true;
	}

	void RenderPipeline::AddScene(std::shared_ptr<Scene> scene_p)
	{
		sceneMapper.insert(std::make_pair(scene_p->identifier, scene_p));
	}

	void RenderPipeline::DeleteScene(std::shared_ptr<Scene> scene_p)
	{
		const std::map<std::string, std::shared_ptr<Scene>>::iterator it = sceneMapper.find(scene_p->identifier);
		if (it != sceneMapper.end())
		{
			sceneMapper.erase(it);
		}
	}

	void RenderPipeline::DeleteScene(std::string identifier_p)
	{
		const std::map<std::string, std::shared_ptr<Scene>>::iterator it = sceneMapper.find(identifier_p);
		if (it != sceneMapper.end())
		{
			sceneMapper.erase(it);
		}
	}

	void RenderPipeline::PreRender()
	{
		if (gammaCorrection)
		{
			glEnable(GL_FRAMEBUFFER_SRGB);
		}
		else
		{
			glDisable(GL_FRAMEBUFFER_SRGB);
		}
	}

	void RenderPipeline::Render(std::vector<Shader*> shaders_p, Camera* camera_p,
								uint32 scrWidth_p, uint32 scrHeight_p,
								mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		for (std::pair<std::string, std::shared_ptr<Scene>> it : sceneMapper)
		{
			std::shared_ptr<Scene> scene = it.second;
			scene->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
						  projection_p, view_p, model_p);
		}
	}

	void RenderPipeline::ForwardRender(std::vector<Shader*> shaders_p, Camera* camera_p,
									   uint32 scrWidth_p, uint32 scrHeight_p,
									   mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		for (std::pair<std::string, std::shared_ptr<Scene>> it : sceneMapper)
		{
			std::shared_ptr<Scene> scene = it.second;
			scene->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
						  projection_p, view_p, model_p);
		}
	}

	void RenderPipeline::InitGBuffer(uint32 scrWidth_p, uint32 scrHeight_p)
	{
		glGenFramebuffers(1, &gBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

		glGenTextures(1, &gPosition);
		glBindTexture(GL_TEXTURE_2D, gPosition);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scrWidth_p, scrHeight_p, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

		glGenTextures(1, &gNormal);
		glBindTexture(GL_TEXTURE_2D, gNormal);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scrWidth_p, scrHeight_p, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

		glGenTextures(1, &gAlbedoSpec);
		glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, scrWidth_p, scrHeight_p, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

		attachments [0] = GL_COLOR_ATTACHMENT0;
		attachments [1] = GL_COLOR_ATTACHMENT1;
		attachments [2] = GL_COLOR_ATTACHMENT2;
		glDrawBuffers(3, attachments);

		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, scrWidth_p, scrHeight_p);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPipeline::DeferredRender(std::vector<Shader*> shaders_p, Camera* camera_p,
										uint32 scrWidth_p, uint32 scrHeight_p,
										mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (std::pair<std::string, std::shared_ptr<Scene>> it : sceneMapper)
		{
			std::shared_ptr<Scene> scene = it.second;
			scene->Render(shaders_p, camera_p, scrWidth_p, scrHeight_p,
						  projection_p, view_p, model_p);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, gNormal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, scrWidth_p, scrHeight_p, 0, 0, scrWidth_p, scrHeight_p, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPipeline::InitPostProcesser(uint32 screenWidth_p, uint32 screenHeight_p)
	{
		postProcesser = new PostProcesser(screenWidth_p, screenHeight_p);
	}

	PostProcesser* RenderPipeline::GetPostProcesser()
	{
		return postProcesser;
	}

	void RenderPipeline::PostProcessRenderToFBO()
	{
		postProcesser->RenderToFBO();
	}

	void RenderPipeline::PostProcess()
	{
		postProcesser->RenderFBO();
	}

	void RenderPipeline::InitShadowMap()
	{
		shadowMappingShader = AssetsManager::GetInstance().shaderMapper.find("ShadowMappingFragment.glsl")->second;
		shadowMappingDepthShader = AssetsManager::GetInstance().shaderMapper.find("ShadowMappingDepthFragment.glsl")->second;
		debugDepthQuadShader = AssetsManager::GetInstance().shaderMapper.find("DebugQuadFragment.glsl")->second;
		glGenFramebuffers(1, &depthMapFBO);
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor [] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPipeline::ShadowMapRender(std::shared_ptr<Light> light_p,
										 std::vector<Shader*> shaders_p, Camera* camera_p,
										 uint32 scrWidth_p, uint32 scrHeight_p,
										 mat4f projection_p, mat4f view_p, mat4f model_p)
	{
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
		lightView = glm::lookAt(light_p->GetPosition(), vec3f(0.0f), vec3f(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;
		shadowMappingDepthShader->Use();
		shadowMappingDepthShader->SetMat4("lightSpaceMatrix", lightSpaceMatrix);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		Render(shaders_p, camera_p, scrWidth_p, scrHeight_p, projection_p, view_p, model_p);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		shadowMappingShader->Use();
		shadowMappingShader->SetMat4("projection", projection_p);
		shadowMappingShader->SetMat4("view", view_p);
		shadowMappingShader->SetVec3("viewPos", camera_p->Position);
		shadowMappingShader->SetVec3("lightPos", light_p->GetPosition());
		shadowMappingShader->SetMat4("lightSpaceMatrix", lightSpaceMatrix);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		Render(shaders_p, camera_p, scrWidth_p, scrHeight_p, projection_p, view_p, model_p);

		debugDepthQuadShader->Use();
		debugDepthQuadShader->SetFloat("near_plane", nearPlane);
		debugDepthQuadShader->SetFloat("far_plane", farPlane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
	}

	void RenderPipeline::ShadingRender()
	{

	}

	void RenderPipeline::InitGrid()
	{
		grid = new Grid();
	}

	void RenderPipeline::RenderGrid(Camera* camera_p, mat4f projection_p, mat4f view_p)
	{
		glEnable(GL_DEPTH_TEST | GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Shader* gridShader = AssetsManager::GetInstance().shaderMapper.find("GridFragment.glsl")->second;
		Shader* shadowMappingShader = AssetsManager::GetInstance().shaderMapper.find("ShadowMappingFragment.glsl")->second;
		Shader* shadowMappingDepthShader = AssetsManager::GetInstance().shaderMapper.find("ShadowMappingDepthFragment.glsl")->second;
		std::vector<Shader*> shaders;
		shaders.push_back(shadowMappingShader);
		shaders.push_back(shadowMappingDepthShader);
		mat4f model = mat4f(1.0f);
		//for (uint32 i = 0; i < shaders.size(); i++)
		//{
		//	shaders [i]->Use();
		//	//shaders [i]->SetMat4("view", view_p);
		//	//shaders [i]->SetMat4("projection", projection_p);
		//	//shaders [i]->SetVec3("cameraPos", camera_p->Position);
		//	shaders [i]->SetMat4("model", model);
		//	grid.Draw(shaders [i]);
		//}
		gridShader->Use();
		gridShader->SetMat4("view", view_p);
		gridShader->SetMat4("projection", projection_p);
		gridShader->SetVec3("cameraPos", camera_p->Position);
		grid->Draw(gridShader);
		glDisable(GL_BLEND);
	}

	void RenderPipeline::InitSkyBox()
	{
		skybox = new SkyBox();
	}

	void RenderPipeline::RenderSkyBox(Camera* camera_p, mat4f projection_p, mat4f view_p)
	{
		if (skyboxOn)
		{
			skybox->Draw(camera_p, projection_p, view_p);
		}
	}
}
// Forward Rendering
// ShadowMap(Geometry -> VS) -> Shading(Drawcall -> Skybox) -> Post-Process(Bloom -> ColorGrading)
// 
// Deferred Rendering
// Rendering G-Buffer -> Deferred Shading
