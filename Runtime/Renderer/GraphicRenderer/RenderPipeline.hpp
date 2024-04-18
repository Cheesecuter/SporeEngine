#pragma once

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

		std::map<std::string, Scene*> m_scene_mapper;
		bool m_skybox_on = true;
		bool m_gamma_correction_on = false;
		bool m_shadow_map_on = false;
		bool m_post_process_on = true;
		std::string m_post_process = "";

		void Initialize();
		void AddScene(Scene* p_scene);
		void DeleteScene(Scene* p_scene);
		void DeleteScene(std::string p_identifier);
		void SetScenePos(uint32 p_scene_pos_x, uint32 p_scene_pos_y);
		vec2f GetScenePos();
		void SetSceneSize(uint32 p_scene_width, uint32 p_scene_height);
		vec2f GetSceneSize();
		void UpdateSceneFBO();
		void UpdateSceneRBO();
		void LightPass(Camera* p_camera,
					   uint32 p_screen_width, uint32 p_screen_height,
					   mat4f p_projection, mat4f p_view, mat4f p_model);
		void PreRender();
		void Render(std::vector<Shader*> p_shaders, Camera* p_camera,
					uint32 p_screen_width, uint32 p_screen_height,
					mat4f p_projection, mat4f p_view, mat4f p_model);
		void ForwardRender(std::vector<Shader*> p_shaders, Camera* p_camera,
						   uint32 p_screen_width, uint32 p_screen_height,
						   mat4f p_projection, mat4f p_view, mat4f p_model);
		void InitGBuffer(uint32 p_screen_width, uint32 p_screen_height);
		void DeferredRender(std::vector<Shader*> p_shaders, Camera* p_camera,
							uint32 p_screen_width, uint32 p_screen_height,
							mat4f p_projection, mat4f p_view, mat4f p_model);
		void InitPostProcesser(uint32 p_screen_width, uint32 p_screen_height, PostProcess* p_post_process);
		PostProcesser* GetPostProcesser();
		void PostProcessRenderToFBO();
		void PostProcessFBO();
		void InitSceneFramebuffer(int32 p_window_width, int32 p_window_height);
		void RenderSceneFramebufferBegin(int32 p_window_width, int32 p_window_height);
		void RenderSceneFramebufferEnd();
		uint32 GetSceneFramebuffer();
		uint32 GetSceneTexture();
		void InitShadowMap();
		void ShadowMapRender(std::shared_ptr<Light> p_light,
							 std::vector<Shader*> p_shaders, Camera* p_camera,
							 uint32 p_screen_width, uint32 p_screen_height,
							 mat4f p_projection, mat4f p_view, mat4f p_model);
		void ShadingRender();
		void InitGrid();
		void RenderGrid(Camera* p_camera, mat4f p_projection, mat4f p_view);
		void InitSkyBox();
		void RenderSkyBox(Camera* p_camera, mat4f p_projection, mat4f p_view);
		
		void initlightbox();
		void renderlightbox(mat4f p_projection, mat4f p_view, mat4f p_model);
		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;

	protected:

	private:
		bool m_initialized;
		uint32 m_g_buffer;
		uint32 m_g_position, m_g_normal, m_g_albedo_specular;
		uint32 m_forward_render_FBO;
		uint32 m_attachments [3];
		uint32 m_RBO_depth;
		PostProcesser* m_post_processer;
		uint32 m_scene_framebuffer;
		uint32 m_scene_texture;
		SkyBox* m_skybox;
		Grid* m_grid;
		const uint32 SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
		uint32 m_scene_pos_x, m_scene_pos_y;
		uint32 m_scene_width, m_scene_height;
		Shader* m_shadow_mapping_shader;
		Shader* m_shadow_mapping_depth_shader;
		Shader* m_debug_depth_quad_shader;
		uint32 m_depth_map, m_depth_map_FBO;
		float32 m_near_plane = 1.0f, m_far_plane = 100.0f;
		mat4x4f m_light_projection, m_light_view, m_light_space_matrix;
	};
}
