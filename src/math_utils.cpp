/**
 * @file math_utils.cpp
 * @brief Core 2D/3D math and vector utility functions for game mechanics.
 * @details Provides optimized calculations for distance, angle trajectory, 
 *          wind drift vectors, and physics helpers used across Raylib and C++ game projects.
 * @author Callum Wade (C6WX)
 * @date 2026
 */

#include <cmath>

/**
 * @struct Vector2D
 * @brief Simple container for 2D position or velocity vectors.
 */
struct Vector2D {
    float x; /**< X-coordinate or horizontal component */
    float y; /**< Y-coordinate or vertical component */
};

/**
 * @brief Calculates the 2D Euclidean distance between two spatial points.
 * @details Uses the Pythagorean theorem: \f$\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}\f$.
 * 
 * @param x1 Starting point X coordinate.
 * @param y1 Starting point Y coordinate.
 * @param x2 Target point X coordinate.
 * @param y2 Target point Y coordinate.
 * @return The straight-line distance as a float.
 */
float CalculateDistance2D(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

/**
 * @brief Applies atmospheric wind force vectors to projectile velocity.
 * @details Offsets bullet trajectory based on real-time API wind speed parameters.
 * 
 * @param currentVelocity The current velocity vector of the projectile.
 * @param windSpeed Speed of wind in meters per second.
 * @param windAngle Wind heading in degrees (0 - 360).
 * @return Updated Vector2D after applying wind acceleration force.
 */
Vector2D ApplyWindDrift(Vector2D currentVelocity, float windSpeed, float windAngle) {
    const float DEG_TO_RAD = 0.0174532925f;
    float rad = windAngle * DEG_TO_RAD;
    
    currentVelocity.x += std::cos(rad) * (windSpeed * 0.05f);
    currentVelocity.y += std::sin(rad) * (windSpeed * 0.05f);
    
    return currentVelocity;
}

/**
 * @brief Linearly interpolates between two float values.
 * @param a Start value.
 * @param b Target value.
 * @param t Interpolation alpha value clamped between 0.0f and 1.0f.
 * @return Interpolated float value.
 */
float Lerp(float a, float b, float t) {
    return a + t * (b - a);
}