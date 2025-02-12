/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __GAME_CAMERA_H__
#define __GAME_CAMERA_H__

#include "../geometry/Geometry.hpp"
#include "GameObject.hpp"

#define DEFAULT_FOV_DEG 45 
#define DEFAULT_NEAR_PLANE 0.1
#define DEFAULT_FAR_PLANE 100


namespace wgame {

class GameCamera : GameObject {
public:
    Point3D position;
    Size size;
    float nearPlane;
    float farPlane;
    GameCamera(
        const Point3D & position, 
        const Size & size, 
        float FOVdeg = DEFAULT_FOV_DEG,
        float nearPlane = DEFAULT_NEAR_PLANE,
        float farPlane = DEFAULT_FAR_PLANE
    );
    void setFOVdeg(float FOVdeg);
    void update() override;
    void * getMatrixValuePtr();
private:
    Vector3D _orientation;
    Vector3D _up;
    float _FOVrad;
    Matrix4D _cameraMatrix;
};

}

#endif
