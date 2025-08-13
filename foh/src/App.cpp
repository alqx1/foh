#include "App.hpp"

#include "gfx/ShaderFiles.hpp"

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
    glm::mat4 model = glm::identity<glm::mat4>();
    while (!window.shouldClose()) {
        renderer.renderTextureQuad(
            image.getTexture(),
            model,
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 1.f)
        );
        window.update();
    }
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
