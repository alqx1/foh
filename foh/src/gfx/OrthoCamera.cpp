#include "gfx/OrthoCamera.hpp"

#include "utils/utils.hpp"

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

void OrthoCamera::zoomCamera(f32 zoom, const glm::vec2 &pivot) {
    glm::vec2 center = (bottomLeft + topRight) / 2.f;
    glm::vec2 size = (topRight - bottomLeft);
    glm::vec2 rightSize = topRight - pivot;
    glm::vec2 leftSize = size - rightSize;

    const f32 zoomMargin = 0.1f;
    f32 scale = 1.f - zoom * zoomMargin;

    leftSize *= scale;
    rightSize *= scale;

    size = leftSize + rightSize;

    if (size.x < 10.f || size.y < 10.f) return;
    if (size.x > 10000.f || size.y > 10000.f) return;

    bottomLeft = pivot - leftSize;
    topRight = pivot + rightSize;

    this->update();
}

void OrthoCamera::update() {
    this->projection = glm::ortho(
        bottomLeft.x, topRight.x, bottomLeft.y, topRight.y
    );
}
