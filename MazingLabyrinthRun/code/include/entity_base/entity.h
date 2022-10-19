#ifndef BASE_ENTITY_HEADER
#define BASE_ENTITY_HEADER
struct Entity {
	int id;
	friend bool operator<(const Entity& l, const Entity& r) { return l.id < r.id; }
};
#endif
