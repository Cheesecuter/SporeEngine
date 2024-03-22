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

	void RenderPipeline::Render(std::vector<Shader> shaders_p, Camera* camera_p,
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

	void RenderPipeline::ForwardRender(std::vector<Shader> shaders_p, Camera* camera_p,
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

	void RenderPipeline::DeferredRender(std::vector<Shader> shaders_p, Camera* camera_p,
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

	void RenderPipeline::CleanUp()
	{
		initialized = false;
	}

	void RenderPipeline::RenderGrid(Camera* camera_p, mat4f projection_p, mat4f view_p)
	{
		glEnable(GL_DEPTH_TEST | GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Grid grid;
		Shader* shader = AssetsManager::GetInstance().shaderMapper.find("GridFragment.glsl")->second;
		shader->Use();
		shader->SetMat4("view", view_p);
		shader->SetMat4("projection", projection_p);
		shader->SetVec3("cameraPos", camera_p->Position);
		grid.Draw(shader);
		glDisable(GL_BLEND);
	}

	void RenderPipeline::InitSkyBox()
	{
		skybox.Init();
	}

	void RenderPipeline::RenderSkyBox(Camera* camera_p, mat4f projection_p, mat4f view_p)
	{
		if (skyboxOn)
		{
			skybox.Draw(camera_p, projection_p, view_p);
		}
	}
}
// Forward Rendering
// ShadowMap(Geometry -> VS) -> Shading(Drawcall -> Skybox) -> Post-Process(Bloom -> ColorGrading)
// Deferred Rendering
// Rendering G-Buffer -> Deferred Shading
