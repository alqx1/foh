#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../utils/utils.hpp"
#include "../gfx/gfx.hpp"

class Window {
public:
    Window(const std::string& title, s32 width, s32 height);
    ~Window();

    glm::ivec2 getSize();
    void setSize(s32 width, s32 height);
    bool shouldClose();
    void update();
private:
    GLFWwindow *handle;
    glm::ivec2 size;

    static void resizeCallback(GLFWwindow* window, int xpos, int ypos);
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
    static void keyCallback(
        GLFWwindow* window, int key, int scancode, int action, int mods
    );
    static void mouseButtonCallback(
        GLFWwindow* window, int button, int action, int mods
    );
};

#endif
