#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <JoltPhysics/Jolt/Jolt.h>
#include <JoltPhysics/Jolt/Math/Vec3.h>

namespace Spore
{
	/**
	 * @brief Convert JPH::Vec3 value to glm::vec3 value.
	 *
	 * This function takes a JPH::Vec3 value `p_value` and converts it to a glm::vec3 value.
	 *
	 * @param p_value The JPH::Vec3 value to convert.
	 * @return The glm::vec3 value.
	 */
	glm::vec3 Vec3f(const JPH::Vec3& p_value);

	/**
	 * @brief Convert JPH::Quat value to glm::vec3 value representing euler angles in degrees.
	 *
	 * This function takes a quaternion `p_value` and converts it to euler angles in degrees,
	 * represented as a glm::vec3 value.
	 *
	 * @param p_value The JPH::Quat value to convert.
	 * @return The glm::vec3 value representing euler angles in degrees.
	 */
	glm::vec3 Vec3f(const JPH::Quat& p_value);

	/**
	 * @brief Convert glm::vec3 value to JPH::Vec3 value.
	 *
	 * This function takes a glm::vec3 value `p_value` and converts it to a JPH::Vec3 value.
	 *
	 * @param p_value The glm::vec3 value to convert.
	 * @return The JPH::Vec3 value.
	 */
	JPH::Vec3 JPHVec3(const glm::vec3& p_value);

	/**
	 * @brief Convert JPH::Quat value to glm::quat value.
	 *
	 * This function takes a JPH::Quat value `p_value` and converts it to a glm::quat value.
	 *
	 * @param p_value The JPH::Quat value to convert.
	 * @return The glm::quat value.
	 */
	glm::quat Quat(const JPH::Quat& p_value);

	/**
	 * @brief Convert glm::quat value to JPH::Quat value.
	 *
	 * This function takes a glm::quat value `p_value` and converts it to a JPH::Quat value.
	 *
	 * @param p_value The glm::quat value to convert.
	 * @return The JPH::Quat value.
	 */
	JPH::Quat JPHQuat(const glm::quat& p_value);
}
