#ifndef APP_HPP
#define APP_HPP

#include "gfx/Renderer.hpp"
#include "gfx/Image.hpp"
#include "gfx/Window.hpp"

#include "utils/GLFWContext.hpp"

class App {
public:
    App(int argc, char *argv[]);

private:
    GLFWContext glfwContext;
    Window window;
    Renderer renderer;
    Image image;

    void loop();

    bool update();

    std::filesystem::path checkArgs(int argc, char *argv[]);
    void initCameraPositionMiddle();
};

#endif
