#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include <Types.hpp>

namespace Spore
{
	class Shader;

	class ShaderObserver
	{
	public:
		virtual ~ShaderObserver();
	};

	class Shader
	{
	public:
		// program ID
		uint32 m_ID;
		std::string m_identifier;
		bool m_alpha_filter_flag;

		// read and construct shader
		Shader(const char* p_vertex_path, const char* p_fragment_path, const char* p_geometry_path = nullptr);
		~Shader();

		// use/activate the program
		void Use() const;
		// uniform tool functions
		void SetBool(const std::string& p_name, bool p_value) const;
		void SetInt(const std::string& p_name, int32 p_value) const;
		void SetFloat(const std::string& p_name, float32 p_value) const;
		// vector functions
		void SetVec2(const std::string& p_name, const vec2f& p_value) const;
		void SetVec2(const std::string& p_name, float32 p_x, float32 p_y) const;
		void SetVec3(const std::string& p_name, const vec3f& p_value) const;
		void SetVec3(const std::string& p_name, float32 p_x, float32 p_y, float32 p_z) const;
		void SetVec4(const std::string& p_name, const vec4f& p_value) const;
		void SetVec4(const std::string& p_name, float32 p_x, float32 p_y, float32 p_z, float32 p_w) const;
		// matrix functions
		void SetMat2(const std::string& p_name, const mat2f& p_mat) const;
		void SetMat3(const std::string& p_name, const mat3f& p_mat) const;
		void SetMat4(const std::string& p_name, const mat4f& p_mat) const;

	protected:

	private:
		void CheckCompileErrors(uint32 p_shader, std::string p_type);
	};
}

#endif