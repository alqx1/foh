#include "gfx/Window.hpp"
#include "GLFW/glfw3.h"
#include "gfx/gfx.hpp"

#include "utils/utils.hpp"

Window::Window(const std::string &title, s32 width, s32 height)
    : size{width, height} {
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
    glfwSetScrollCallback(this->handle, this->scrollCallback);

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
}

void Window::update() {
    this->mouse.scrolled = false;

    glfwPollEvents();
    glfwSwapBuffers(this->handle);

    this->mouse.delta = this->mouse.position - this->mouse.previous;
    this->mouse.previous = this->mouse.position;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateButtons(keys);
    updateButtons(mouse.buttons);
}

glm::ivec2 Window::getSize() const {
    return this->size;
}

Button Window::getKey(GLenum key) {
    auto it = this->keys.find(key);
    if (it != this->keys.end()) {
        return it->second;
    }
    this->keys.insert_or_assign(key, (Button){0});
    return this->keys[key];
}

Button Window::getMouseButton(GLenum button) {
    auto it = this->mouse.buttons.find(button);
    if (it != this->mouse.buttons.end()) {
        return it->second;
    }
    this->mouse.buttons.insert_or_assign(button, (Button){0});
    return this->mouse.buttons[button];
}

glm::vec2 Window::getMousePos() const {
    return this->mouse.position;
}

glm::vec2 Window::getMouseDelta() const {
    return this->mouse.delta;
}

bool Window::hasScrolled() const {
    return this->mouse.scrolled;
}

double Window::getScrollOffset() const {
    return this->mouse.scrollOffset;
}

void Window::setKeyState(GLenum key, bool down) {
    auto it = this->keys.find(key);
    if (it == this->keys.end()) {
        this->keys.insert_or_assign(key, (Button){0});
    }
    this->keys[key].down = down;
}
void Window::setMouseButtonState(GLenum button, bool down) {
    auto it = this->mouse.buttons.find(button);
    if (it == this->mouse.buttons.end()) {
        this->mouse.buttons.insert_or_assign(button, (Button){0});
    }
    this->mouse.buttons[button].down = down;
}

void Window::setMousePos(const glm::vec2 &pos) {
    this->mouse.position = pos;
}

void Window::updateButtons(std::unordered_map<GLenum, Button> &buttons) {
    for (auto it = buttons.begin(); it != buttons.end(); it++) {
        it->second.pressed = it->second.down && !it->second.last;
        it->second.last = it->second.down;
    }
}

void Window::setSize(s32 width, s32 height) {
    this->size.x = width;
    this->size.y = height;
}

void Window::setRenderer(Renderer *renderer) {
    this->renderer = renderer;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->handle);
}

void Window::resizeCallback(GLFWwindow *window, int xpos, int ypos) {
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
    w->setSize(xpos, ypos);
    glViewport(0, 0, xpos, ypos);

    if (w->renderer) {
        const glm::vec2 bottomLeft = w->renderer->getCamera().getBottomLeft();
        w->renderer->setCameraArea(
            bottomLeft, bottomLeft + glm::vec2(xpos, ypos)
        );
    }
}

void Window::cursorCallback(GLFWwindow *window, double xpos, double ypos) {
    Window *w = static_cast<Window *>(
        glfwGetWindowUserPointer(window)
    );
    glm::vec2 newPos(xpos, w->getSize().y - ypos);
    w->mouse.position = newPos;
}

void Window::keyCallback(
    GLFWwindow *window, int key, int scancode, int action, int mods
) {
    Window *w = static_cast<Window *>(
        glfwGetWindowUserPointer(window)
    );
    switch (action) {
    case GLFW_RELEASE:
        w->setKeyState(key, false);
        break;
    case GLFW_PRESS:
        w->setKeyState(key, true);
        break;
    }
}

void Window::mouseButtonCallback(
    GLFWwindow *window, int button, int action, int mods
) {
    Window *w = static_cast<Window *>(
        glfwGetWindowUserPointer(window)
    );
    switch (action) {
    case GLFW_RELEASE:
        w->setMouseButtonState(button, false);
        break;
    case GLFW_PRESS:
        w->setMouseButtonState(button, true);
        break;
    }
}

void Window::scrollCallback(
    GLFWwindow* window, double xoffset, double yoffset
) {
    Window *w = static_cast<Window *>(
        glfwGetWindowUserPointer(window)
    );
    w->mouse.scrollOffset = yoffset;
    w->mouse.scrolled = true;
}
