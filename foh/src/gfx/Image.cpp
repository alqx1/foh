#include "gfx/Image.hpp"

Image::Image(const std::filesystem::path &path) {
    glGenTextures(1, &this->texture.handle);
    this->load(path);
}

Image::~Image() {
    glDeleteTextures(1, &this->texture.handle);
}

void Image::load(const std::filesystem::path &path) {
    glBindTexture(GL_TEXTURE_2D, this->texture.handle);

    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER
    );
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    u8 *data = stbi_load(path.c_str(), &texture.size.x, &texture.size.y, &channels, 0);

    if (data) {
        GLenum format;
        switch (channels) {
            case 1:
                format = GL_RED; break;
            case 3:
                format = GL_RGB; break;
            case 4:
                format = GL_RGBA; break;
            default:
                std::cerr << "Unsupported image format!\n";
                exit(1);
        }

        glTexImage2D(
            GL_TEXTURE_2D, 0, format, texture.size.x, texture.size.y,
            0, format, GL_UNSIGNED_BYTE, data
        );
        stbi_image_free(data);
    }
    else {
        std::cerr << "Failed to load image!\n";
        exit(1);
    }
}

Texture Image::getTexture() {
    return this->texture;
}
