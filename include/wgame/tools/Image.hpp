/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_IMAGE_H__
#define __WG_IMAGE_H__
 
#include <tinygltf/stb_image.h>
 
 
namespace wgame {

class Image {
public:    
    Image(const char * filename);
    ~Image();
    int getWidth() const;
    int getHeight() const;
    int getNumberOfChannels() const;
    unsigned char * getData() const;
private:
    int _width; 
    int _height;
    int _numberOfChannels;
    unsigned char * _data;
};

}
 
#endif
 