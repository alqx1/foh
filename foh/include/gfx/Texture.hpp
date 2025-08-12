#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "gfx/gfx.hpp"
#include "glm/glm.hpp"

struct Texture {
    GLuint handle;
    glm::ivec2 size;
};

#endif
