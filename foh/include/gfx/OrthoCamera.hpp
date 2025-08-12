#ifndef ORTHO_CAMERA_HPP
#define ORTHO_CAMERA_HPP

#include "glm/glm.hpp"

class OrthoCamera {
public:
    OrthoCamera();
    OrthoCamera(const glm::vec2 &bottomLeft, const glm::vec2 &topRight);

    glm::mat4 getProj() const;

    void setArea(const glm::vec2 &bottomLeft, const glm::vec2 &topRight);

private:
    glm::vec2 bottomLeft;
    glm::vec2 topRight;
    glm::mat4 projection;

    void update();
};

#endif
