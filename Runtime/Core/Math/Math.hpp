#pragma once

namespace Spore
{
	static constexpr float PI = 3.141592653589793238462643383679f;
	static constexpr float EPSILON = 1e-6f;

	/**
	 * @brief Convert degrees to radians.
	 *
	 * This function converts an angle from degrees to radians.
	 *
	 * @param p_value The angle value in degrees.
	 * @return The equivalent angle value in radians.
	 */
	constexpr float Radians(float p_value);

	/**
	 * @brief Convert radians to degrees.
	 *
	 * This function converts an angle from radians to degrees.
	 *
	 * @param p_value The angle value in radians.
	 * @return The equivalent angle value in degrees.
	 */
	constexpr float Degrees(float p_value);

	/**
	 * @brief Clamp a value to a specified range.
	 *
	 * This function limits the p_value to the specified range [p_min, p_max].
	 * If the value is less than p_min, it returns p_min.
	 * If the value is greater than p_max, it returns p_max.
	 * Otherwise, it returns the p_value itself.
	 *
	 * @tparam T The type of the input value.
	 * @param p_value The value to be clamped.
	 * @param p_min The minimum value of the range.
	 * @param p_max The maximum value of the range.
	 * @return The clamped value within the specified range.
	 */
	template <typename T>
	constexpr T Clamp(T p_value, T p_min, T p_max);

	/**
	 * @brief Calculate the square of a value.
	 *
	 * This function calculates the square of a value by multiplying it with itself.
	 *
	 * @tparam T The type of the input value.
	 * @param p_value The input value whose square is to be calculated.
	 * @return The square of the input value.
	 */
	template <typename T>
	constexpr T Square(T p_value);

	/**
	 * @brief Calculate the cube of a value.
	 *
	 * This function calculates the cube of a value by multiplying it with itself three times.
	 *
	 * @tparam T The type of the input value.
	 * @param p_value The input value whose cube is to be calculated.
	 * @return The cube of the input value.
	 */
	template <typename T>
	constexpr T Cubed(T p_value);

	/**
	 * @brief Get the sign of a value.
	 *
	 * This function returns the sign of a value:
	 *   - If the value is negative, returns -1.
	 *   - If the value is zero or positive, returns 1.
	 *
	 * @tparam T The type of the input value.
	 * @param p_value The input value whose sign is to be determined.
	 * @return -1 if the input value is negative, 1 otherwise.
	 */
	template <typename T>
	constexpr T Sign(T p_value);

	/**
	 * @brief Check if a value is a power of 2.
	 *
	 * This function checks if a value is a power of 2.
	 *
	 * @tparam T The type of the input value.
	 * @param p_value The input value to be checked.
	 * @return true if the input value is a power of 2, false otherwise.
	 */
	template <typename T>
	constexpr bool IsPowerOf2(T p_value);
}
