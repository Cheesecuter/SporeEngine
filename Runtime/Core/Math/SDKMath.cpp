#include <SDKMath.hpp>

namespace Spore
{
	glm::vec3 Vec3f(const JPH::Vec3& p_value)
	{
		return glm::vec3(p_value [0], p_value [1], p_value [2]);
	}

	JPH::Vec3 JPHVec3(const glm::vec3& p_value)
	{
		return JPH::Vec3(p_value.x, p_value.y, p_value.z);
	}
}