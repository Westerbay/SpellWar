/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/tools/Image.hpp>

namespace wgame {

Image::Image() {}

Image::Image(const String & filename, bool flipVertical) {
    _filename = filename;
    _flip = flipVertical;
    if (flipVertical) {
        stbi_set_flip_vertically_on_load(true);
    }
    _data = std::shared_ptr<unsigned char>(
        stbi_load(filename.c_str(), &_width, &_height, &_numberOfChannels, STBI_default
    ));
    stbi_set_flip_vertically_on_load(false);
}

int Image::getWidth() const {
    return _width;
}

int Image::getHeight() const {
    return _height;
}

int Image::getNumberOfChannels() const {
    return _numberOfChannels;
}

unsigned char * Image::getData() const {
    return _data.get();
}

}
