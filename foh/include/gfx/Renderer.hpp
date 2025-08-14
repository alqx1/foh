#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../utils/utils.hpp"

#include "Shader.hpp"
#include "OrthoCamera.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Image.hpp"

enum ShaderType {
    COLOR,
    IMAGE
};

class Renderer {
public:
    Renderer();

    void addShader(
        const ShaderType type, const std::string &vertShader,
        const std::string &fragShader
    );
    std::unique_ptr<Shader>& getShader(const ShaderType type);

    OrthoCamera& getCamera();
    void setCameraArea(
        const glm::vec2 &bottomLeft, const glm::vec2 &topRight
    );
    void moveCameraArea(const glm::vec2 &move);

    void renderColorQuad(
        const glm::vec2 &size, const glm::vec4 &color, const glm::mat4 &model
    );
    void renderTextureQuad(
        const struct Texture &texture, const glm::mat4 &model,
        const glm::vec2 &uv_min, const glm::vec2 &uv_max
    );
    void renderImage(const Image &image);

  private:
    std::unordered_map<ShaderType, std::unique_ptr<Shader>> shaders;
    OrthoCamera camera;
    VAO vao;
    VBO vbo, ibo;
};

#endif
