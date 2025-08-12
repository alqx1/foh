#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "../utils/utils.hpp"
#include "gfx.hpp"
#include "Texture.hpp"

class Image {
public:
    Image(const std::filesystem::path &path);
    ~Image();

    Texture getTexture();

private:
    Texture texture;

    void load(const std::filesystem::path &path);
};

#endif
