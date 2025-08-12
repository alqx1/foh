#include "gfx/Renderer.hpp"

#include "utils/utils.hpp"
#include "gfx/Texture.hpp"

Renderer::Renderer() 
: vao{}, vbo(true, GL_ARRAY_BUFFER),
    ibo(true, GL_ELEMENT_ARRAY_BUFFER) {
}

void Renderer::addShader(const ShaderType type, const Shader &shader) {
    shaders.insert_or_assign(type, shader);
}

Shader Renderer::getShader(const ShaderType type) {
    auto it = shaders.find(type);
    if (it != shaders.end()) {
        return it->second;
    }
    else {
        std::cerr << "Couldn't find shader type! : " << type << "\n";
        exit(1);
    }
}

void Renderer::setCameraArea(
    const glm::vec2 &bottomLeft, const glm::vec2 &topRight
) {
    this->camera.setArea(bottomLeft, topRight);
}

void Renderer::renderColorQuad(
    const glm::vec2 &size, const glm::vec4 &color, const glm::mat4 &model
) {
    const Shader &shader = this->getShader(ShaderType::COLOR);
    shader.useProgram();
    // shader.setUniVec4f("u_color", color);
    shader.setUniMat4("model", model);
    shader.setUniMat4("proj", this->camera.getProj());

    vbo.buffer(
        (f32[]) {
            0, 0, 0,
            0, size.y, 0,
            size.x, 0, 0,
            size.x, size.y, 0,
        }, 12 * sizeof(f32)
    );

    ibo.buffer(
        (u32[]) {
            0, 1, 2,
            1, 2, 3
        }, 6 * sizeof(u32)
    );

    vao.addAttrib(vbo, 0, 3, GL_FLOAT, 0, 0);
    vao.bind();
    ibo.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::renderTextureQuad(
    const struct Texture &texture, const glm::mat4 &model,
    const glm::vec2 &uv_min, const glm::vec2 &uv_max
) {
    const Shader &shader = this->getShader(ShaderType::COLOR);
    shader.useProgram();
    shader.setUniMat4("model", model);
    shader.setUniMat4("proj", this->camera.getProj());
    shader.setUniTex2D("tex", texture, 0);

    const glm::vec2 size = texture.size;
    vbo.buffer(
        (f32[]) {
            0, 0, 0,
            0, size.y, 0,
            size.x, 0, 0,
            size.x, size.y, 0,

            uv_min.x, uv_min.y,
            uv_min.x, uv_max.y,
            uv_max.x, uv_min.y,
            uv_max.x, uv_max.y
        }, (12 + 8)* sizeof(f32)
    );

    ibo.buffer(
        (u32[]) {
            0, 1, 2,
            1, 2, 3
        }, 6 * sizeof(u32)
    );

    vao.addAttrib(vbo, 0, 3, GL_FLOAT, 0, 0);
    vao.addAttrib(vbo, 1, 2, GL_FLOAT, 0, 12 * sizeof(f32));

    vao.bind();
    ibo.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
}
