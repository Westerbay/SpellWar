/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_CUBE_MAP_DRAWER_H__
#define __WG_CUBE_MAP_DRAWER_H__

#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/Texture2D.hpp"
#include "../opengl/Shader.hpp"
#include "../geometry/Cuboid.hpp"

#define CUBEMAP_VERTEX_SHADER "shaders/cubeMapDrawer.vert"
#define CUBEMAP_FRAGMENT_SHADER "shaders/cubeMapDrawer.frag"


namespace wgame {

class CubeMapDrawer {
public:
    CubeMapDrawer();
    void setFaces(
        const Image & imagePositiveX,
        const Image & imageNegativeX,
        const Image & imagePositiveY,
        const Image & imageNegativeY,
        const Image & imagePositiveZ,
        const Image & imageNegativeZ
    );
    void draw() const;
protected:
    class CubeMapDrawerShader : public Shader {
    public:
        CubeMapDrawerShader();
    };
private:
    Cuboid _cube;
    VertexArrayObject _vao;
    Texture2D _texture;
    CubeMapDrawerShader _shader;
};

}

#endif
