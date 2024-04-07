#include <SDKMath.hpp>

namespace Spore
{
	glm::vec3 Vec3f(const JPH::Vec3& p_value)
	{
		return glm::vec3(p_value [0], p_value [1], p_value [2]);
	}

	glm::vec3 Vec3f(const JPH::Quat& p_value)
	{
		glm::vec3 angle = glm::eulerAngles(Quat(p_value));
		glm::vec3 degree = glm::degrees(angle);
		return glm::vec3(degree [0], degree [1], degree [2]);
	}

	JPH::Vec3 JPHVec3(const glm::vec3& p_value)
	{
		return JPH::Vec3(p_value.x, p_value.y, p_value.z);
	}

	glm::quat Quat(const JPH::Quat& p_value)
	{
		JPH::Vec4 quat = p_value.GetXYZW();
		return glm::quat(quat[3], quat [0], quat [1], quat [2]);
	}

	JPH::Quat JPHQuat(const glm::quat& p_value)
	{
		return JPH::Quat(p_value.x, p_value.y, p_value.z, p_value.w);
	}
}