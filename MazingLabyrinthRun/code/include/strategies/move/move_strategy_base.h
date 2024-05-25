#ifndef MOVE_STRATEGY_BASE_HEADER
#define MOVE_STRATEGY_BASE_HEADER

#include <SFML/System/Vector2.hpp>

class MoveStrategy {
public:
	virtual sf::Vector2f get_velocity() = 0;
	virtual void finalize_move() = 0;
};

#endif  // !MOVE_STRATEGY_BASE_HEADER
