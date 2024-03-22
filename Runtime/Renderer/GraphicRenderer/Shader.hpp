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
		uint32 ID;
		std::string identifier;

		// read and construct shader
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		~Shader();

		// use/activate the program
		void Use() const;
		// uniform tool functions
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int32 value) const;
		void SetFloat(const std::string& name, float32 value) const;
		// vector functions
		void SetVec2(const std::string& name, const vec2f& value) const;
		void SetVec2(const std::string& name, float32 x, float32 y) const;
		void SetVec3(const std::string& name, const vec3f& value) const;
		void SetVec3(const std::string& name, float32 x, float32 y, float32 z) const;
		void SetVec4(const std::string& name, const vec4f& value) const;
		void SetVec4(const std::string& name, float32 x, float32 y, float32 z, float32 w) const;
		// matrix functions
		void SetMat2(const std::string& name, const mat2f& mat) const;
		void SetMat3(const std::string& name, const mat3f& mat) const;
		void SetMat4(const std::string& name, const mat4f& mat) const;

	protected:

	private:
		void CheckCompileErrors(uint32 shader, std::string type);
	};
}

#endif