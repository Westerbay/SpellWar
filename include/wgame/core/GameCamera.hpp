/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_GAME_CAMERA_H__
#define __WG_GAME_CAMERA_H__

#include "../geometry/Geometry.hpp"
#include "../opengl/UniformBufferObject.hpp"
#include "GameObject.hpp"


#define DEFAULT_FOV_DEG 45.0f
#define DEFAULT_NEAR_PLANE 0.1f
#define DEFAULT_FAR_PLANE 100.0f

#define CAMERA_MATRICES_POINT 0


namespace wgame {

struct CameraMatrices {
    Matrix4D background;
    Matrix4D world;   
    Matrix4D HUD; 
};

class GameCamera : public GameObject {
public:
    GameCamera();
    void setSize(const Size & size);
    void setFOVdeg(float FOVDeg);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
    void attachGameObject(GameObject * gameObject);
    void apply() const;
    void update() override;    
private:
    UniformBufferObject _ubo;
    float _FOVDeg;    
    float _nearPlane;
    float _farPlane;
    GameObject * _attachedObject;
    CameraMatrices _cameraMatrices;
};

}

#endif
