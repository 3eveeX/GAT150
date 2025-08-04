#pragma once
#include <algorithm>
#include <cmath>

namespace whermst::math {
		constexpr float pi = 3.141592653589793238462643383279502f;
		constexpr float twoPi = 2 * pi;
		constexpr float halfPi = pi / 2;

		/// <summary>
		/// Converts radians to degrees.
		/// </summary>
		/// <param name="rad">The radian measure to convert.</param>
		/// <returns>The degree equivalent of the radian measure.</returns>
		constexpr float radToDeg(float rad) { return rad * 180 / pi; }
		/// <summary>
		/// Converts degrees to radians.
		/// </summary>
		/// <param name="deg">The degree measure to convert.</param>
		/// <returns>The radian equivalent of the degree measure.</returns>
		constexpr float degToRad(float deg) { return deg * pi / 180; }
		

		constexpr int wrap(int value, int min, int max) {
			int range = max - min;
			int result = (value - min) % range;
			if (result < 0) result += range;

			return result + min;
		}

		inline float wrap(float value, float min, float max) {
			float range = max - min;
			float result = std::fmodf(value - min, range);
			if (result < 0) result += range;
			return result + min;
		}

		using std::min;
		using std::max;
		using std::clamp;
		using std::sqrtf;
		using std::sqrt;
		using std::sin;
		using std::asin;
		using std::sinf;
		using std::asinf;
		using std::cos;
		using std::acos;
		using std::cosf;
		using std::acosf;
		using std::tan;
		using std::atan;
		using std::tanf;
		using std::atanf;
		using std::atan2;
		using std::atan2f;
	
}
