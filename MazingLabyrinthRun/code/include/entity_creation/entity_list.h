#ifndef ENTITY_TYPE_HEADER
#define ENTITY_TYPE_HEADER

enum class EntityType : int {
	player = 0,
	zombie = 1,
};

inline bool is_regular_mob(EntityType type) { return static_cast<int>(type) >= 0 && static_cast<int>(type) < 5000; }
#endif