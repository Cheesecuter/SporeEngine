#pragma once

#include <Types.hpp>
#include <Object.hpp>

namespace Spore
{
	class Light : public Object 
	{
	public:
		Light(const std::string& p_identifier);
		~Light();
		vec3f GetLightColor();
		void Render(std::vector<Shader*> p_shaders, Camera* p_camera,
					uint32 p_screen_width, uint32 p_screen_height,
					mat4f p_projection, mat4f p_view, mat4f p_model);
	protected:

	private:
		vec3f m_light_color = vec3f(1.0f, 1.0f, 1.0f);
		std::map<std::string, Model*> m_model_mapper;
	};
}
