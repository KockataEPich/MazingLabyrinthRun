#ifndef TEXTURE_ENUM_HEADER
#define TEXTURE_ENUM_HEADER

enum class Textures { tree, rock };

#include <array>

static std::array<Textures, 2> all_textures{Textures::tree, Textures::rock};

#endif