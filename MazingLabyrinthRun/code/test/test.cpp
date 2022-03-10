#include "../include/tile.h"
#include <catch2/catch_all.hpp>

TEST_CASE("TestTile", "[TILE]") {
	Tile tile;
	CHECK(tile.getSize().x == 36.0f);
}
