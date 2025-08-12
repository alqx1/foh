#include "gfx/Window.hpp"
#include "gfx/ShaderFiles.hpp"
#include "gfx/Renderer.hpp"
#include "gfx/Image.hpp"

int main (int argc, char *argv[]) {
    Window window("foh", 400, 400);

    if (argc != 2) {
        std::cerr << "Wrong usage!\nUsage: foh <image path>\n";
        exit(1);
    }
    std::filesystem::path path("seal.jpg");
    Image image(path);

    glm::vec2 windowSize = window.getSize();
    Renderer renderer;
    renderer.setCameraArea(glm::vec2(0.f), windowSize);
    renderer.addShader(COLOR, ShaderFiles::vertShader, ShaderFiles::fragShader);

    glm::mat4 model = glm::identity<glm::mat4>();
    while (!window.shouldClose()) {
        glm::vec2 windowSize = window.getSize();
        renderer.setCameraArea(glm::vec2(0.f), windowSize);
        renderer.renderTextureQuad(
            image.getTexture(),
            model,
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 1.f)
        );
        window.update();
    }
}
