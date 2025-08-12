#ifndef VAO_HPP
#define VAO_HPP

#include "../utils/utils.hpp"

#include "gfx.hpp"
#include "VBO.hpp"

class VAO {
public:
    VAO();
    ~VAO();

    void bind();
    void addAttrib(
        VBO &vbo, GLuint index, GLint size, GLenum type,
        GLsizei stride, size_t offset
    );
private:
    GLuint handle;
};

#endif
