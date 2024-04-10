#pragma once

#ifndef SE_TYPE
#define SE_TYPE

#include <map>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <cstdarg>
#include <thread>
#include <mutex>
#include <Windows.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#ifndef STBI_WINDOWS_UTF8
#define STBI_WINDOWS_UTF8
#endif
#include <stb_image.h>

#include <Global.hpp>
#include <Math.hpp>
#include <SDKMath.hpp>

namespace Spore
{
	// signed integer
	using int8 = std::int8_t;
	using int16 = std::int16_t;
	using int32 = std::int32_t;
	using int64 = std::int64_t;

	// unsigned integer
	using uint8 = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint64 = std::uint64_t;

	using float32 = float;
	using float64 = double;

	// floating-point num vector
	using vec2f = glm::vec2;
	using vec3f = glm::vec3;
	using vec4f = glm::vec4;

	// double-precision floating-point num vector
	using vec2d = glm::dvec2;
	using vec3d = glm::dvec3;
	using vec4d = glm::dvec4;

	// signed integer num vecter
	using vec2i = glm::ivec2;
	using vec3i = glm::ivec3;
	using vec4i = glm::ivec4;

	// unsigned integer num vector
	using vec2u = glm::uvec2;
	using vec3u = glm::uvec3;
	using vec4u = glm::uvec4;

	// boolean vector
	using vec2b = glm::bvec2;
	using vec3b = glm::bvec3;
	using vec4b = glm::bvec4;

	// floating-point num matrix
	using mat2x2f = glm::mat2x2;
	using mat2x3f = glm::mat2x3;
	using mat2x4f = glm::mat2x4;
	using mat3x2f = glm::mat3x2;
	using mat3x3f = glm::mat3x3;
	using mat3x4f = glm::mat3x4;
	using mat4x2f = glm::mat4x2;
	using mat4x3f = glm::mat4x3;
	using mat4x4f = glm::mat4x4;
	
	using mat2f = glm::mat2;
	using mat3f = glm::mat3;
	using mat4f = glm::mat4;

	// double-precision floating-point num matrix
	using mat2x2d = glm::dmat2x2;
	using mat2x3d = glm::dmat2x3;
	using mat2x4d = glm::dmat2x4;
	using mat3x2d = glm::dmat3x2;
	using mat3x3d = glm::dmat3x3;
	using mat3x4d = glm::dmat3x4;
	using mat4x2d = glm::dmat4x2;
	using mat4x3d = glm::dmat4x3;
	using mat4x4d = glm::dmat4x4;

	using mat2d = glm::dmat2;
	using mat3d = glm::dmat3;
	using mat4d = glm::dmat4;

	using quat = glm::quat;
}

#endif
