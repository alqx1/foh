#include "gfx/VBO.hpp"

VBO::VBO(bool dynamic, GLuint type)
: dynamic{dynamic}, type{type} {
    glGenBuffers(1, &this->handle);
}

VBO::~VBO() {
    glDeleteBuffers(1, &this->handle);
}

void VBO::bind() {
    glBindBuffer(this->type, this->handle);
}

void VBO::buffer(void *data, size_t size) {
    this->bind();
    glBufferData(
        this->type, size, data,
        this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
    );
}
