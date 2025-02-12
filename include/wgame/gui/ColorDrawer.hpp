/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __COLOR_DRAWER_H__
#define __COLOR_DRAWER_H__

#include "../opengl/VertexArrayObject.hpp"
#include "../geometry/Cuboid.hpp"


namespace wgame {

class ColorDrawer {
public:
    void drawCuboid(const Cuboid & cuboid, const ColorRGB & color);
private:
    VertexArrayObject _vao;
};

}

#endif
