#ifndef ORTHO_CAMERA_HPP
#define ORTHO_CAMERA_HPP

#include "glm/glm.hpp"
#include "utils/utils.hpp"

class OrthoCamera {
public:
    OrthoCamera();
    OrthoCamera(const glm::vec2 &bottomLeft, const glm::vec2 &topRight);

    glm::mat4 getProj() const;
    glm::vec2 getBottomLeft() const;
    glm::vec2 getTopRight() const;

    void setArea(const glm::vec2 &bottomLeft, const glm::vec2 &topRight);
    void moveArea(const glm::vec2 &move);

    void zoom(f32 zoom);

    void update();

private:
    glm::vec2 bottomLeft;
    glm::vec2 topRight;
    glm::mat4 projection;
};

#endif
