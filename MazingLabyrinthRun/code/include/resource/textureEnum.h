#ifndef TEXTURE_ENUM_HEADER
#define TEXTURE_ENUM_HEADER

enum class Textures { tree, rock, grass };

#include <array>

static std::array<Textures, 3> all_textures{Textures::tree, Textures::rock, Textures::grass};

#endif