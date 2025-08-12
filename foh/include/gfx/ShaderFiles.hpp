#ifndef SHADER_FILES_HPP
#define SHADER_FILES_HPP

#include "../utils/utils.hpp"

namespace ShaderFiles {

const std::string vertShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

out vec2 out_uv;

uniform mat4 proj, model;

void main() {
    gl_Position = proj * model * vec4(aPos, 1.f);
    out_uv = aUv;
}
)";

const std::string fragShader = R"(
#version 330 core

out vec4 out_fragColor;

in vec2 out_uv;

uniform sampler2D tex;

void main() {
    out_fragColor = texture(tex, out_uv);
}
)";

}

#endif
