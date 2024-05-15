#pragma once

namespace Spore
{
#ifndef ST_SHADER_UNIFORM_TYPE
#define ST_SHADER_UNIFORM_TYPE
	enum class ShaderUniformType
	{
		NONE,
		BOOL,
		INT,
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4
	};
#endif
}