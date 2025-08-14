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
    this->topRight -= zoom;
    this->bottomLeft += zoom;

    if (this->topRight.x < this->bottomLeft.x ||
            this->topRight.y < this->bottomLeft.y) {
        this->topRight += zoom;
        this->bottomLeft -= zoom;
    }

    this->update();
}

void OrthoCamera::update() {
    this->projection = glm::ortho(
        bottomLeft.x, topRight.x, bottomLeft.y, topRight.y
    );
}
