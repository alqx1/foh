#include "gfx/Window.hpp"
#include "GLFW/glfw3.h"
#include "gfx/gfx.hpp"

#include "utils/utils.hpp"

Window::Window(const std::string &title, s32 width, s32 height)
    : size{width, height} {
    if (!glfwInit()) {
        std::cerr << "Could not init GLFW\n";
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (this->handle == nullptr) {
        std::cerr << "Window couldn't be opened!\n";
        std::exit(1);
    }
    glfwMakeContextCurrent(this->handle);

    glfwSetMouseButtonCallback(this->handle, this->mouseButtonCallback);
    glfwSetKeyCallback(this->handle, this->keyCallback);
    glfwSetCursorPosCallback(this->handle, this->cursorCallback);
    glfwSetFramebufferSizeCallback(this->handle, this->resizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Could not init GLAD\n";
        glfwTerminate();
        exit(1);
    }

    glfwSwapInterval(0);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowUserPointer(this->handle, this);
    this->update();
}

Window::~Window() {
    glfwDestroyWindow(this->handle);
    glfwTerminate();
}

void Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(this->handle);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::ivec2 Window::getSize() {
    return this->size;
}

void Window::setSize(s32 width, s32 height) {
    this->size.x = width;
    this->size.y = height;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->handle);
}

void Window::resizeCallback(GLFWwindow *window, int xpos, int ypos) {
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
    w->setSize(xpos, ypos);
    glViewport(0, 0, xpos, ypos);
}

void Window::cursorCallback(GLFWwindow *window, double xpos, double ypos) {
}

void Window::keyCallback(
    GLFWwindow *window, int key, int scancode, int action, int mods
) {
}

void Window::mouseButtonCallback(
    GLFWwindow *window, int button, int action, int mods
) {
}
