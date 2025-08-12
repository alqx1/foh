#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../utils/utils.hpp"

#include "Shader.hpp"
#include "OrthoCamera.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

enum ShaderType {
    COLOR,
    IMAGE
};

class Renderer {
public:
    Renderer();

    void addShader(const ShaderType type, const Shader &shader);
    Shader getShader(const ShaderType type);

    void setCameraArea(
        const glm::vec2 &bottomLeft, const glm::vec2 &topRight
    );

    void renderColorQuad(
        const glm::vec2 &size, const glm::vec4 &color, const glm::mat4 &model
    );

    void renderTextureQuad(
        const struct Texture &texture, const glm::mat4 &model,
        const glm::vec2 &uv_min, const glm::vec2 &uv_max
    );

private:
    std::unordered_map<ShaderType, Shader> shaders;
    OrthoCamera camera;
    VAO vao;
    VBO vbo, ibo;
};

#endif
