#pragma once
#include <cstdlib>
#include <random>
#include "Math/Math.h"
#include "Math/Vector2.h"

namespace whermst::random {

        /// <summary>
        /// Returns a reference to a static Mersenne Twister random number generator instance.
        /// </summary>
        /// <returns>A reference to a static std::mt19937 random number generator, initialized with a random seed.</returns>
        inline std::mt19937& generator() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            return gen;
        }

        /// <summary>
        /// Seeds the random number generator with the specified value.
        /// </summary>
        /// <param name="value">The seed value to initialize the random number generator.</param>
        inline void seed(unsigned int value) {
            generator().seed(value);
        }

        /// <summary>
        /// Generates a random integer within the specified range, inclusive.
        /// </summary>
        /// <param name="min">The minimum value of the range (inclusive).</param>
        /// <param name="max">The maximum value of the range (inclusive).</param>
        /// <returns>A randomly generated integer between min and max, inclusive.</returns>
        inline int getInt(int min, int max) {
            std::uniform_int_distribution<> dist(min, max);
            return dist(generator());
        }

        /// <summary>
        /// Returns an integer in the range [0, max - 1] by calling an overloaded getInt function.
        /// </summary>
        /// <param name="max">The exclusive upper bound for the random integer to generate.</param>
        /// <returns>An integer value greater than or equal to 0 and less than max.</returns>
        inline int getInt(int max) {
            return getInt(0, max - 1);
        }

        /// <summary>
        /// Generates a random integer using a static uniform integer distribution and a generator.
        /// </summary>
        /// <returns>A randomly generated integer.</returns>
        inline int getInt() {
            static std::uniform_int_distribution<> dist;
            return dist(generator());
        }

        /// <summary>
        /// Generates a random real number within the specified range.
        /// </summary>
        /// <typeparam name="T">The floating-point type to use for the random number (defaults to float).</typeparam>
        /// <param name="min">The lower bound of the range (inclusive).</param>
        /// <param name="max">The upper bound of the range (exclusive).</param>
        /// <returns>A random real number of type T in the range [min, max).</returns>
        template <typename T = float>
        inline T getReal(T min, T max) {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(generator());
        }

        /// <summary>
        /// Generates a real number in the range [0, max).
        /// </summary>
        /// <typeparam name="T">The floating-point type to use for the generated number. Defaults to float.</typeparam>
        /// <param name="max">The exclusive upper bound for the generated real number.</param>
        /// <returns>A real number of type T in the range [0, max).</returns>
        template <typename T = float>
        inline T getReal(T max) {
            return getReal(static_cast<T>(0), static_cast<T>(max));
        }

        /// <summary>
        /// Generates a random real number in the range [0, 1).
        /// </summary>
        /// <typeparam name="T">The floating-point type of the generated number. Defaults to float.</typeparam>
        /// <returns>A random real number of type T in the range [0, 1).</returns>
        template <typename T = float>
        inline T getReal() {
            static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
            return dist(generator());
        }

        /// <summary>
        /// Generates a random boolean value with equal probability for true or false.
        /// </summary>
        /// <returns>A randomly generated boolean value (true or false) with a 50% chance for each.</returns>
        inline bool getBool() {
            static std::bernoulli_distribution dist(0.5);
            return dist(generator());
        }

        /// <summary>
        /// Generates a random 2D unit vector on the circumference of the unit circle.
        /// </summary>
        /// <returns>A whermst::vec2 representing a point on the unit circle, with both x and y components in the range [-1, 1].</returns>
        inline whermst::vec2 onUnitCircle() {
            float radians = getReal<float>(math::twoPi);
            whermst::vec2 v;
            v.x = math::cosf(radians);
            v.y = math::sinf(radians);
            return v;
        }
}