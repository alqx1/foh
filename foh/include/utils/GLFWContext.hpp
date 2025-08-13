#ifndef GLFWCONTEXT_HPP
#define GLFWCONTEXT_HPP

#include "../gfx/gfx.hpp"
#include "utils.hpp"

class GLFWContext {
public:
    GLFWContext(s32 major, s32 minor, bool resizable) {
        if (!glfwInit()) {
            std::cerr << "Could not init GLFW\n";
            exit(1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);
    }

    ~GLFWContext() {
        glfwTerminate();
        std::cout << "context\n";
    }
};

#endif
