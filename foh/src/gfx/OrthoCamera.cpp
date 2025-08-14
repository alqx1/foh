#include "gfx/OrthoCamera.hpp"

#include "utils/utils.hpp"

#define DEFAULT_ZOOM_MARGIN 50

OrthoCamera::OrthoCamera()
: bottomLeft(), topRight() {
    this->update();
}

OrthoCamera::OrthoCamera(
    const glm::vec2 &bottomLeft, const glm::vec2 &topRight
) : bottomLeft{bottomLeft}, topRight{topRight} {
    this->update();
}

glm::mat4 OrthoCamera::getProj() const {
    return this->projection;
}

glm::vec2 OrthoCamera::getBottomLeft() const {
    return this->bottomLeft;
}

glm::vec2 OrthoCamera::getTopRight() const {
    return this->topRight;
}

void OrthoCamera::setArea(
    const glm::vec2 &bottomLeft, const glm::vec2 &topRight
) {
    this->bottomLeft = bottomLeft;
    this->topRight = topRight;
    this->update();
}

void OrthoCamera::moveArea(const glm::vec2 &move) {
    this->bottomLeft += move;
    this->topRight += move;
    this->update();
}

void OrthoCamera::zoom(f32 zoom) {
    glm::vec2 center = (bottomLeft + topRight) / 2.f;
    glm::vec2 halfSize = (topRight - bottomLeft) / 2.f;

    float scale = 1.f - zoom * 0.1f;

    halfSize *= scale;

    if (halfSize.x * 2 < 10.f || halfSize.y * 2 < 10.f) return;
    if (halfSize.x * 2 > 10000.f || halfSize.y * 2 > 10000.f) return;

    bottomLeft = center - halfSize;
    topRight = center + halfSize;

    this->update();
}

void OrthoCamera::update() {
    this->projection = glm::ortho(
        bottomLeft.x, topRight.x, bottomLeft.y, topRight.y
    );
}
