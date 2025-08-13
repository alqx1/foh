#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../utils/utils.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/Renderer.hpp"

struct Button {
    bool pressed : 1;
    bool down : 1;
    bool last : 1;
};

class Window {
public:
    Window(const std::string& title, s32 width, s32 height);
    ~Window();

    Button getKey(GLenum key);
    Button getMouseButton(GLenum button);
    glm::vec2 getMousePos() const;

    glm::ivec2 getSize() const;
    void setSize(s32 width, s32 height);

    void setRenderer(Renderer *renderer);

    bool shouldClose();
    void update();

private:
    GLFWwindow *handle;
    glm::ivec2 size;

    Renderer *renderer = nullptr;

    std::unordered_map<GLenum, Button> keys;
    struct Mouse {
        std::unordered_map<GLenum, Button> buttons;
        glm::vec2 position;
        glm::vec2 delta;
    } mouse;

    void setKeyState(GLenum key, bool down);
    void setMouseButtonState(GLenum button, bool down);
    void setMousePos(const glm::vec2 &pos);

    void updateKeys();
    void updateMouseButtons();

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
