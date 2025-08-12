#include "gfx/Window.hpp"
#include "gfx/ShaderFiles.hpp"
#include "gfx/Shader.hpp"
#include "gfx/Renderer.hpp"
#include "gfx/Image.hpp"

int main (int argc, char *argv[]) {
    Window window("foh", 100, 100);

    std::filesystem::path path("seal.jpg");
    Image image(path);

    Shader shader(ShaderFiles::vertShader, ShaderFiles::fragShader);

    glm::vec2 windowSize = window.getSize();
    Renderer renderer;
    renderer.setCameraArea(glm::vec2(0.f), windowSize);
    renderer.addShader(COLOR, shader);

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
