#include <Math.hpp>
#include <algorithm>
#include <cmath>
#include <limits>

namespace Spore
{

	constexpr float Radians(float p_value)
	{
		return p_value * (PI / 180.0f);
	}

	constexpr float Degrees(float p_value)
	{
		return p_value * (180.0f / PI);
	}

	template <typename T>
	constexpr T Clamp(T p_value, T p_min, T p_max)
	{
		return std::min(std::max(p_value, p_min), p_max);
	}

	template <typename T>
	constexpr T Square(T p_value)
	{
		return p_value * p_value;
	}

	template <typename T>
	constexpr T Cubed(T p_value)
	{
		return p_value * p_value * p_value;
	}

	template <typename T>
	constexpr T Sign(T p_value)
	{
		return p_value < 0 ? T(-1) : T(1);
	}

	template <typename T>
	constexpr bool IsPowerOf2(T p_value)
	{
		return (p_value & (p_value - 1)) == 0;
	}
}