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
	glm::vec3 Vec3f(const JPH::Vec3& p_value);
	glm::vec3 Vec3f(const JPH::Quat& p_value);
	JPH::Vec3 JPHVec3(const glm::vec3& p_value);
	glm::quat Quat(const JPH::Quat& p_value);
	JPH::Quat JPHQuat(const glm::quat& p_value);
}
