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
#include "../opengl/UniformBufferObject.hpp"
#include "GameObject.hpp"
#include <iostream>

#define DEFAULT_FOV_DEG 45.0f
#define DEFAULT_NEAR_PLANE 0.1f
#define DEFAULT_FAR_PLANE 100.0f

#define CAMERA_MATRIX_POINT 0


namespace wgame {

class GameCamera : public GameObject {
public:
    GameCamera();
    void setSize(const Size & size);
    void setFOVdeg(float FOVDeg);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
    void attachGameObject(GameObject * gameObject);
    void update() override;
    void render() override;
protected:
    class UniformCamera : public UniformBufferObject {
    public:
        UniformCamera();
    };
private:
    UniformCamera _ubo;
    float _FOVDeg;    
    float _nearPlane;
    float _farPlane;
    GameObject * _attachedObject;
    Matrix4D _cameraMatrix;
};

}

#endif
