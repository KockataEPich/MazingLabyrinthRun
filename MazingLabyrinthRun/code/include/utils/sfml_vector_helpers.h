#ifndef SFML_VECTOR_HELPERS
#define SFML_VECTOR_HELPERS

#include <SFML/System/Vector2.hpp>
#include <cstdlib>

inline sf::Vector2f operator/(sf::Vector2f lhs, sf::Vector2f rhs) { return {lhs.x / rhs.x, lhs.y / rhs.y}; }
inline sf::Vector2f operator*(sf::Vector2f lhs, sf::Vector2f rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y}; }
inline sf::Vector2f operator/(float lhs, sf::Vector2f rhs) { return {lhs / rhs.x, lhs / rhs.y}; }
inline sf::Vector2f operator/(sf::Vector2f lhs, int rhs) { return {lhs.x / rhs, lhs.y / rhs}; }
inline sf::Vector2f abs(sf::Vector2f vec) { return {std::abs(vec.x), std::abs(vec.y)}; }

template <typename ...Args>
inline void do_for_x_and_y(sf::Vector2f& vector, std::function<void(float&, Args...)> function, Args... args) {
	function(vector.x, args...);
	function(vector.y, args...);
}

template<typename... Args>
inline void do_per_x_and_y(sf::Vector2f& input_vector,
                           sf::Vector2f reference_vector,
                           std::function<void(float&, float, Args...)> function,
                           Args... args) {

	function(input_vector.x, reference_vector.x, args...);
	function(input_vector.y, reference_vector.y, args...);
}

template<typename... Args>
inline void do_on_x_and_y(sf::Vector2f& input,
                          sf::Vector2f& input2,
                          std::function<void(float&, float&, Args...)> function,
                          Args... args) {

	function(input.x, input2.x, args...);
	function(input.y, input2.y, args...);
}

template<typename... Args>
inline sf::Vector2f produce_x_and_y(const sf::Vector2f& input,
                            const sf::Vector2f& input2,
                            std::function<float(const float, const float, Args...)> function,
                            Args... args) {
	return {function(input.x, input2.x, args...), function(input.y, input2.y, args...)};
}

#endif