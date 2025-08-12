#ifndef VBO_HPP
#define VBO_HPP

#include "../utils/utils.hpp"
#include "gfx.hpp"

class VBO {
public:
    VBO(bool dynamic, GLuint type);
    ~VBO();

    void bind();
    void buffer(void *data, size_t size);

private:
    GLuint handle;
    bool dynamic; // dynamic or static draw
    GLuint type; // vbo or ibo
};

#endif
