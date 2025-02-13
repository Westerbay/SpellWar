/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameCamera.hpp>


namespace wgame {

GameCamera::GameCamera() {
    _FOVDeg = DEFAULT_FOV_DEG;
    _nearPlane = DEFAULT_NEAR_PLANE;
    _farPlane = DEFAULT_FAR_PLANE;
    _attachedObject = nullptr;
    _up = Vector3D(0.0f, 1.0f, 0.0f);
    _orientation = Vector3D(0.0f, 0.0f, 1.0f);
    _cameraMatrix = Matrix4D(1.0f);
}

void GameCamera::setSize(const Size & size) {
    hitbox.size = Vector3D(size.width, size.height, 0.0f);
}

void GameCamera::setFOVdeg(float FOVDeg) {
    _FOVDeg = FOVDeg;
}

void GameCamera::setNearPlane(float nearPlane) {
    _nearPlane = nearPlane;
}

void GameCamera::setFarPlane(float farPlane) {
    _farPlane = farPlane;
}

void GameCamera::attachGameObject(GameObject * gameObject) {
    _attachedObject = gameObject;
}

void GameCamera::update() {
    Point3D position(0.0f);
    if (_attachedObject != nullptr) {
        position = _attachedObject -> getHitbox().position;
    }

    Matrix4D view(1.0f);
    Matrix4D projection(1.0f);    
    view = glm::lookAt(position, position + _orientation, _up);
    projection = glm::perspective(
        glm::radians(_FOVDeg), 
        (float) (hitbox.size.x / hitbox.size.y),
         _nearPlane, 
         _farPlane
    );
    
    _cameraMatrix = projection * view;
}

Matrix4D GameCamera::getMatrix() {
    return _cameraMatrix;
}

}
