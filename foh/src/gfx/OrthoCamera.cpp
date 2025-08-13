#include "gfx/OrthoCamera.hpp"

#include "utils/utils.hpp"

OrthoCamera::OrthoCamera()
: bottomLeft(), topRight(){
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

void OrthoCamera::setArea(
    const glm::vec2 &bottomLeft, const glm::vec2 &topRight
) {
    this->bottomLeft = bottomLeft;
    this->topRight = topRight;
    this->update();
}

glm::vec2 OrthoCamera::getBottomLeft() const {
    return this->bottomLeft;
}

glm::vec2 OrthoCamera::getTopRight() const {
    return this->topRight;
}

void OrthoCamera::update() {
    this->projection = glm::ortho(
        bottomLeft.x, topRight.x, bottomLeft.y, topRight.y
    );
}
