#pragma once
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Types.hpp>
#include <Object.hpp>

namespace Spore
{
	class Light : public Object 
	{
	public:
		Light(const std::string& identifier_p);
		~Light();
		vec3f GetLightColor();
		void Render(std::vector<Shader*> shaders_p, Camera* camera_p,
					uint32 scrWidth_p, uint32 scrHeight_p,
					mat4f projection_p, mat4f view_p, mat4f model_p);
	protected:

	private:
		vec3f lightColor = vec3f(1.0f, 1.0f, 1.0f);
		std::map<std::string, Model*> modelMapper;
	};
}

#endif
