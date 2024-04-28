#include <RenderPipeline.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	RenderPipeline::RenderPipeline() : m_initialized(false)
	{

	}

	RenderPipeline::~RenderPipeline()
	{
	}

	void RenderPipeline::Initialize()
	{
		if (m_initialized)
		{
			return;
		}

		m_initialized = true;
	}

	void RenderPipeline::SetBackgroundColor(vec4f p_background_color)
	{
		m_background_color = p_background_color;
	}

	vec4f RenderPipeline::GetBackgroundColor()
	{
		return m_background_color;
	}

	void RenderPipeline::AddScene(Scene* p_scene)
	{
		m_scene_mapper.insert(std::make_pair(p_scene->m_identifier, p_scene));
	}

	void RenderPipeline::DeleteScene(Scene* p_scene)
	{
		const std::map<std::string, Scene*>::iterator it = m_scene_mapper.find(p_scene->m_identifier);
		if (it != m_scene_mapper.end())
		{
			m_scene_mapper.erase(it);
		}
	}

	void RenderPipeline::DeleteScene(std::string p_identifier)
	{
		const std::map<std::string, Scene*>::iterator it = m_scene_mapper.find(p_identifier);
		if (it != m_scene_mapper.end())
		{
			m_scene_mapper.erase(it);
		}
	}

	void RenderPipeline::SetScenePos(uint32 p_scene_pos_x, uint32 p_scene_pos_y)
	{
		m_scene_pos_x = p_scene_pos_x;
		m_scene_pos_y = p_scene_pos_y;
	}

	vec2f RenderPipeline::GetScenePos()
	{
		vec2f scenePos(m_scene_pos_x, m_scene_pos_y);
		return scenePos;
	}

	void RenderPipeline::SetSceneSize(uint32 p_scene_width, uint32 p_scene_height)
	{
		m_scene_width = p_scene_width;
		m_scene_height = p_scene_height;
	}

	vec2f RenderPipeline::GetSceneSize()
	{
		vec2f sceneSize(m_scene_width, m_scene_height);
		return sceneSize;
	}

	void RenderPipeline::LightPass(Camera* p_camera,
								   uint32 p_screen_width, uint32 p_screen_height,
								   mat4f p_projection, mat4f p_view, mat4f p_model)
	{
		/*Shader* lightningShader = AssetsManager::GetInstance().m_shader_mapper ["LightingFragment.glsl"];
		lightningShader->Use();
		lightningShader->SetMat4("projection", p_projection);
		lightningShader->SetMat4("view", p_view);
		lightningShader->SetVec3("viewPos", p_camera->m_position);
		lightningShader->SetVec3("lightPos", );
		lightingShader.SetInt("blinn", blinn);*/
	}

	void RenderPipeline::PreRender()
	{
		if (m_gamma_correction_on)
		{
			glEnable(GL_FRAMEBUFFER_SRGB);
		}
		else
		{
			glDisable(GL_FRAMEBUFFER_SRGB);
		}
	}

	void RenderPipeline::Render(Camera* p_camera,
								uint32 p_screen_width, uint32 p_screen_height,
								float32 p_delta_time)
	{
		for (std::pair<std::string, Scene*> it : m_scene_mapper)
		{
			Scene* scene = it.second;
			scene->Render(p_camera, m_scene_width, m_scene_height, p_delta_time);
		}
	}

	void RenderPipeline::ForwardRender(std::vector<Shader*> p_shaders, Camera* p_camera,
									   uint32 p_screen_width, uint32 p_screen_height,
									   mat4f p_projection, mat4f p_view, mat4f p_model,
									   float32 p_delta_time)
	{
		for (std::pair<std::string, Scene*> it : m_scene_mapper)
		{
			Scene* scene = it.second;
			scene->Render(p_camera, p_screen_width, p_screen_height, p_delta_time);
		}
	}

	void RenderPipeline::InitGBuffer(uint32 p_screen_width, uint32 p_screen_height)
	{
		glGenFramebuffers(1, &m_g_buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_g_buffer);

		glGenTextures(1, &m_g_position);
		glBindTexture(GL_TEXTURE_2D, m_g_position);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, p_screen_width, p_screen_height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_g_position, 0);

		glGenTextures(1, &m_g_normal);
		glBindTexture(GL_TEXTURE_2D, m_g_normal);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, p_screen_width, p_screen_height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_g_normal, 0);

		glGenTextures(1, &m_g_albedo_specular);
		glBindTexture(GL_TEXTURE_2D, m_g_albedo_specular);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_screen_width, p_screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_g_albedo_specular, 0);

		m_attachments [0] = GL_COLOR_ATTACHMENT0;
		m_attachments [1] = GL_COLOR_ATTACHMENT1;
		m_attachments [2] = GL_COLOR_ATTACHMENT2;
		glDrawBuffers(3, m_attachments);

		glGenRenderbuffers(1, &m_RBO_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO_depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, p_screen_width, p_screen_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO_depth);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			ConsoleLogger::GetInstance().Logger()->error("RenderPipeline::InitGBuffer: Framebuffer not complete");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPipeline::initlightbox()
	{
		const unsigned int NR_LIGHTS = 40;
		lightPositions;
		lightColors;
		srand(13);
		for (unsigned int i = 0; i < NR_LIGHTS; i++)
		{
			// calculate slightly random offsets
			float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
			// also calculate random color
			float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			lightColors.push_back(glm::vec3(rColor, gColor, bColor));
		}
	}

	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	void renderCube()
	{
		// initialize (if necessary)
		if (cubeVAO == 0)
		{
			float vertices [] = {
				// back face
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
				// front face
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				// left face
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				// right face
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
				// bottom face
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				// top face
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
				 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
			};
			glGenVertexArrays(1, &cubeVAO);
			glGenBuffers(1, &cubeVBO);
			// fill buffer
			glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			// link vertex attributes
			glBindVertexArray(cubeVAO);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		// render Cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	void RenderPipeline::renderlightbox(mat4f p_projection, mat4f p_view, mat4f p_model)
	{
		Shader* shaderLightBoxShader = AssetsManager::GetInstance().m_shader_mapper ["DeferredLightBoxFragment.glsl"];
		shaderLightBoxShader->Use();
		shaderLightBoxShader->SetMat4("projection", p_projection);
		shaderLightBoxShader->SetMat4("view", p_view);
		for (unsigned int i = 0; i < lightPositions.size(); i++)
		{
			p_model = glm::mat4(1.0f);
			p_model = glm::translate(p_model, lightPositions [i]);
			p_model = glm::scale(p_model, glm::vec3(0.125f));
			shaderLightBoxShader->SetMat4("model", p_model);
			shaderLightBoxShader->SetVec3("lightColor", lightColors [i]);
			renderCube();
		}
	}
	// renderQuad() renders a 1x1 XY quad in NDC
	// -----------------------------------------
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	void renderQuad()
	{
		if (quadVAO == 0)
		{
			float quadVertices [] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void RenderPipeline::DeferredRender(std::vector<Shader*> p_shaders, Camera* p_camera,
										uint32 p_screen_width, uint32 p_screen_height,
										mat4f p_projection, mat4f p_view, mat4f p_model,
										float32 p_delta_time)
	{
		//glViewport(m_scene_pos_x, m_scene_pos_y, m_scene_width, m_scene_height);
		glBindFramebuffer(GL_FRAMEBUFFER, m_g_buffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (std::pair<std::string, Scene*> it : m_scene_mapper)
		{
			Scene* scene = it.second;
			scene->Render(p_camera, p_screen_width, p_screen_height, p_delta_time);
		}
		RenderSkyBox(p_camera, p_projection, p_view);
		RenderGrid(p_camera, p_projection, p_view);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		Shader* shaderLightingPassShader = AssetsManager::GetInstance().m_shader_mapper ["DeferredShadingFragment.glsl"];
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderLightingPassShader->Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_g_position);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_g_normal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_g_albedo_specular);

		for (unsigned int i = 0; i < lightPositions.size(); i++)
		{
			shaderLightingPassShader->SetVec3("lights[" + std::to_string(i) + "].Position", lightPositions [i]);
			shaderLightingPassShader->SetVec3("lights[" + std::to_string(i) + "].Color", lightColors [i]);
			// update attenuation parameters and calculate radius
			const float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
			const float linear = 0.7f;
			const float quadratic = 1.8f;
			shaderLightingPassShader->SetFloat("lights[" + std::to_string(i) + "].Linear", linear);
			shaderLightingPassShader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
			// then calculate radius of light volume/sphere
			const float maxBrightness = std::fmaxf(std::fmaxf(lightColors [i].r, lightColors [i].g), lightColors [i].b);
			float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
			shaderLightingPassShader->SetFloat("lights[" + std::to_string(i) + "].Radius", radius);
		}
		shaderLightingPassShader->SetVec3("viewPos", p_camera->m_position);

		renderQuad();

		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_g_buffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(m_scene_pos_x, m_scene_pos_y, p_screen_width, p_screen_height, m_scene_pos_x, m_scene_pos_y, p_screen_width, p_screen_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPipeline::InitPostProcesser(uint32 p_screen_width, uint32 p_screen_height, PostProcess* p_post_process)
	{
		m_post_processer = new PostProcesser(p_screen_width, p_screen_height, p_post_process);
	}

	PostProcesser* RenderPipeline::GetPostProcesser()
	{
		return m_post_processer;
	}

	void RenderPipeline::PostProcessRenderToFBO()
	{
		m_post_processer->RenderToFBO();
		glViewport(0, 0, m_scene_width, m_scene_height);
	}

	void RenderPipeline::PostProcessFBO()
	{
		m_post_processer->RenderFBO();
	}

	void RenderPipeline::UpdateSceneFBO()
	{
		uint32 frameBufferTexture = m_post_processer->GetFrameBufferTexture();
		glBindTexture(GL_TEXTURE_2D, frameBufferTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_scene_width, m_scene_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTexture, 0);
	}

	void RenderPipeline::UpdateSceneRBO()
	{
		uint32 renderBuffer = m_post_processer->GetDepthBuffer();
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_scene_width, m_scene_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(m_scene_pos_x, m_scene_pos_y, m_scene_width, m_scene_height);
	}

	void RenderPipeline::InitSceneFramebuffer(int32 p_window_width, int32 p_window_height)
	{
		glGenFramebuffers(1, &m_scene_framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_scene_framebuffer);
		glGenTextures(1, &m_scene_texture);
		glBindTexture(GL_TEXTURE_2D, m_scene_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_window_width, p_window_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_scene_texture, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			ConsoleLogger::GetInstance().Logger()->error("RenderPipeline::InitSceneFramebuffer: Framebuffer not complete");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPipeline::RenderSceneFramebufferBegin(int32 p_window_width, int32 p_window_height)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_scene_framebuffer);
		glViewport(0, 0, p_window_width, p_window_height);
	}

	void RenderPipeline::RenderSceneFramebufferEnd()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32 RenderPipeline::GetSceneFramebuffer()
	{
		return m_scene_framebuffer;
	}

	uint32 RenderPipeline::GetSceneTexture()
	{
		return m_scene_texture;
	}

	void RenderPipeline::InitShadowMap()
	{
		m_shadow_mapping_shader = AssetsManager::GetInstance().m_shader_mapper.find("ShadowMappingFragment.glsl")->second;
		m_shadow_mapping_depth_shader = AssetsManager::GetInstance().m_shader_mapper.find("ShadowMappingDepthFragment.glsl")->second;
		m_debug_depth_quad_shader = AssetsManager::GetInstance().m_shader_mapper.find("DebugQuadFragment.glsl")->second;
		glGenFramebuffers(1, &m_depth_map_FBO);
		glGenTextures(1, &m_depth_map);
		glBindTexture(GL_TEXTURE_2D, m_depth_map);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor [] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_map, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPipeline::ShadowMapRender(std::shared_ptr<Light> p_light,
										 std::vector<Shader*> p_shaders, Camera* p_camera,
										 uint32 p_screen_width, uint32 p_screen_height,
										 mat4f p_projection, mat4f p_view, mat4f p_model,
										 float32 p_delta_time)
	{
		m_light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, m_near_plane, m_far_plane);
		m_light_view = glm::lookAt(p_light->GetPosition(), vec3f(0.0f), vec3f(0.0f, 1.0f, 0.0f));
		m_light_space_matrix = m_light_projection * m_light_view;
		m_shadow_mapping_depth_shader->Use();
		m_shadow_mapping_depth_shader->SetMat4("lightSpaceMatrix", m_light_space_matrix);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_FBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		Render(p_camera, p_screen_width, p_screen_height, p_delta_time);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_shadow_mapping_shader->Use();
		m_shadow_mapping_shader->SetMat4("projection", p_projection);
		m_shadow_mapping_shader->SetMat4("view", p_view);
		m_shadow_mapping_shader->SetVec3("viewPos", p_camera->m_position);
		m_shadow_mapping_shader->SetVec3("lightPos", p_light->GetPosition());
		m_shadow_mapping_shader->SetMat4("lightSpaceMatrix", m_light_space_matrix);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_depth_map);
		Render(p_camera, p_screen_width, p_screen_height, p_delta_time);

		m_debug_depth_quad_shader->Use();
		m_debug_depth_quad_shader->SetFloat("near_plane", m_near_plane);
		m_debug_depth_quad_shader->SetFloat("far_plane", m_far_plane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_depth_map);
	}

	void RenderPipeline::ShadingRender()
	{

	}

	void RenderPipeline::InitGrid()
	{
		m_grid = new Grid();
	}

	void RenderPipeline::RenderGrid(Camera* p_camera, mat4f p_projection, mat4f p_view)
	{
		if (m_grid_on)
		{
			glEnable(GL_DEPTH_TEST | GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			Shader* gridShader = AssetsManager::GetInstance().m_shader_mapper.find("GridFragment.glsl")->second;
			gridShader->Use();
			gridShader->SetMat4("view", p_view);
			gridShader->SetMat4("projection", p_projection);
			gridShader->SetVec3("cameraPos", p_camera->m_position);
			m_grid->Draw(gridShader);
			glDisable(GL_BLEND);
		}
	}

	void RenderPipeline::InitSkyBox()
	{
		m_skybox = new SkyBox();
	}

	void RenderPipeline::RenderSkyBox(Camera* p_camera, mat4f p_projection, mat4f p_view)
	{
		if (m_skybox_on)
		{
			m_skybox->Draw(p_camera, p_projection, p_view);
		}
	}
}
// Forward Rendering
// ShadowMap(Geometry -> VS) -> Shading(Drawcall -> Skybox) -> Post-Process(Bloom -> ColorGrading)
// 
// Deferred Rendering
// Rendering G-Buffer -> Deferred Shading
