#include "App.hpp"

#include "gfx/ShaderFiles.hpp"
#include <thread>

#define WINDOW_TITLE ("foh")
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

#define OPENGL_MAJOR 3
#define OPENGL_MINOR 3
#define OPENGL_RESIZABLE (true)

App::App(int argc, char *argv[])
: glfwContext(OPENGL_MAJOR, OPENGL_MINOR, OPENGL_RESIZABLE),
    window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT),
    renderer(), image(checkArgs(argc, argv))
{
    renderer.addShader(
        ShaderType::IMAGE,
        ShaderFiles::vertShader,
        ShaderFiles::fragShader
    );
    window.setRenderer(&this->renderer);
    initCameraPositionMiddle();

    loop();
}

void App::loop() {
    using namespace std::chrono;

    glm::mat4 model = glm::identity<glm::mat4>();
    const duration<f64, std::milli> target = 1s / 60.f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer.renderImage(image);
    window.update(true);
    while (!window.shouldClose()) {
        const auto start = high_resolution_clock::now();

        if(this->update()) {
            renderer.renderImage(image);
            window.update(true);
        }
        else {
            window.update(false);
        }

        const auto end = high_resolution_clock::now();

        const duration<f64, std::milli> elapsed = end - start;
        std::this_thread::sleep_for(target - elapsed);
    }
}

bool App::update() {
    bool updated = false;
    if (window.getMouseButton(GLFW_MOUSE_BUTTON_LEFT).down) {
        auto &camera = renderer.getCamera();
        glm::vec2 cameraArea = camera.getTopRight() - camera.getBottomLeft();
        glm::vec2 zoom = cameraArea / glm::vec2(window.getSize());
        renderer.moveCameraArea(-window.getMouseDelta() * zoom);
        updated = true;
    }

    if (window.hasScrolled()) {
        auto &camera = renderer.getCamera();
        glm::vec2 cameraArea = camera.getTopRight() - camera.getBottomLeft();
        glm::vec2 mousePos = window.getMousePos();
        glm::vec2 adjustedPos =
            camera.getBottomLeft() +
            mousePos * (cameraArea / glm::vec2(window.getSize()));
        renderer.getCamera().zoomCamera(
            window.getScrollOffset(),
            adjustedPos
        );
        updated = true;
    }

    return updated;
}

std::filesystem::path App::checkArgs(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong usage!\nUsage: foh <image path>\n";
        exit(1);
    }
    return std::filesystem::path(argv[1]);
}

void App::initCameraPositionMiddle() {
    struct Texture tex = image.getTexture();
    const glm::ivec2 imageSize = tex.size;

    glm::ivec2 middlePoint = imageSize / 2;
    middlePoint -= window.getSize() / 2;
    renderer.setCameraArea(
        middlePoint, middlePoint + window.getSize()
    );
}
