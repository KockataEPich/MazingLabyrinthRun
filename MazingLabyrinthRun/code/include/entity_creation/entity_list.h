#ifndef ENTITY_TYPE_HEADER
#define ENTITY_TYPE_HEADER

enum class EntityType : int {
	player = 0,
	zombie = 1,

	grass_lands_1 = 5000,
};

inline bool is_regular_mob(EntityType type) { return static_cast<int>(type) >= 0 && static_cast<int>(type) < 5000; }
inline bool is_walkalbe_tile(EntityType type) {
	return static_cast<int>(type) >= 5000 && static_cast<int>(type) < 5100;
}
#endif