#ifndef SHADER_HPP
#define SHADER_HPP

#include "gfx.hpp"
#include "../utils/utils.hpp"

class Shader {
public:
    Shader(const std::string &vertSource, const std::string &fragSource);
    ~Shader();
    
    void useProgram() const;
    u64 getProgram() const;

    void setUniVec2f(const std::string &name, const glm::vec2 &vec) const;
    void setUniVec3f(const std::string &name, const glm::vec3 &vec) const;
    void setUniVec4f(const std::string &name, const glm::vec4 &vec) const;

    void setUniMat4(const std::string &name, const glm::mat4 &mat) const;

    void setUniTex2D(const std::string &name, struct Texture texture, GLint n) const;

  private:
    u64 vertHandle, fragHandle, programHandle;

    static void compileShader(u64 shader, const std::string &source);
};

#endif
