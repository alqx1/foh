#include "gfx/Shader.hpp"

#include "gfx/gfx.hpp"
#include "gfx/Texture.hpp"
#include "utils/utils.hpp"

Shader::Shader(const std::string &vertSource, const std::string &fragSource) {
    this->programHandle = glCreateProgram();

    this->vertHandle = glCreateShader(GL_VERTEX_SHADER);
    if (this->vertHandle == 0) {
        std::cerr << "Vertex shader wasn't created!\n";
    }
    this->fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
    if (this->fragHandle == 0) {
        std::cerr << "Fragment shader wasn't created!\n";
    }

    compileShader(this->vertHandle, vertSource);
    compileShader(this->fragHandle, fragSource);

    glAttachShader(this->programHandle, this->vertHandle);
    glAttachShader(this->programHandle, this->fragHandle);

    glLinkProgram(this->programHandle);

    GLint linked;
    glGetProgramiv(this->programHandle, GL_LINK_STATUS, &linked);
    if(linked == GL_FALSE) {
        char buf[512];
        GLint maxlength = 0;
	    glGetProgramiv(this->programHandle, GL_INFO_LOG_LENGTH, &maxlength);
        glGetProgramInfoLog(this->programHandle, maxlength, &maxlength, buf);

        glDeleteProgram(this->programHandle);

        glDeleteShader(this->vertHandle);
        glDeleteShader(this->fragHandle);

        std::cerr << "Couldn't link shader!\n";
        exit(1);
    }

    glDetachShader(this->programHandle, this->vertHandle);
    glDetachShader(this->programHandle, this->fragHandle);
}

void Shader::compileShader(u64 shader, const std::string &source) {
    GLint compiled;
    glShaderSource(shader, 1, (const char **)&source, NULL); // i dont get the pointer stuff
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        char infoLog[1024];
        int length;
        glGetShaderInfoLog(shader, 1024, &length, infoLog);
        glDeleteShader(shader);
        std::cerr << infoLog << "\n";
        exit(1);
    }
}

Shader::~Shader() {
    glDeleteShader(this->vertHandle);
    glDeleteShader(this->fragHandle);
    glDeleteProgram(this->programHandle);
}

void Shader::useProgram() const {
    glUseProgram(this->programHandle);
}

u64 Shader::getProgram() const {
    return this->programHandle;
}

void Shader::setUniVec2f(const std::string &name, const glm::vec2 &vec) const {
    this->useProgram();
    glUniform2f(
        glGetUniformLocation(this->programHandle, name.c_str()),
        vec.x, vec.y
    );
}

void Shader::setUniVec3f(const std::string &name, const glm::vec3 &vec) const {
    this->useProgram();
    glUniform3f(
        glGetUniformLocation(this->programHandle, name.c_str()),
        vec.x, vec.y, vec.z
    );
}

void Shader::setUniVec4f(const std::string &name, const glm::vec4 &vec) const {
    this->useProgram();
    glUniform4f(
        glGetUniformLocation(this->programHandle, name.c_str()),
        vec.x, vec.y, vec.z, vec.w
    );
}

void Shader::setUniMat4(const std::string &name, const glm::mat4 &mat) const {
    this->useProgram();
    glUniformMatrix4fv(
        glGetUniformLocation(this->programHandle, name.c_str()), 1, GL_FALSE,
        glm::value_ptr(mat)
    );
}

void Shader::setUniTex2D(
    const std::string &name, struct Texture texture, GLint n
) const {
    glUseProgram(this->programHandle);
    glActiveTexture(GL_TEXTURE0 + n);
    glBindTexture(GL_TEXTURE_2D, texture.handle);
    glUniform1i(glGetUniformLocation(this->programHandle, name.c_str()), n);
}
