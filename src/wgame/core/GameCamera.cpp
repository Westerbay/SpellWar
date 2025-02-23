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
    _cameraMatrix = Matrix4D(1.0f);
    _cameraMatrixStatic = Matrix4D(1.0f);
    _ubo.configure(sizeof(Matrix4D));
    _ubo.setBindingPoint(CAMERA_MATRIX_POINT);
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
    Matrix3D orientation = hitbox.orientation;
    
    if (_attachedObject != nullptr) {
        position = _attachedObject -> getHitbox().position;
        orientation = _attachedObject -> getHitbox().orientation;
    }
    
    Matrix4D projection = glm::perspective(
        glm::radians(_FOVDeg), 
        (float) (hitbox.size.x / hitbox.size.y),
         _nearPlane, 
         _farPlane
    );
    Matrix4D view = glm::lookAt(position, position + orientation[2], orientation[1]);
    
    _cameraMatrix = projection * view;
    _cameraMatrixStatic = projection * Matrix4D(Matrix3D(view));
}

void GameCamera::applyToBackground() {
    _ubo.setData(glm::value_ptr(_cameraMatrixStatic), sizeof(Matrix4D));
}

void GameCamera::applyToWorld() {
    _ubo.setData(glm::value_ptr(_cameraMatrix), sizeof(Matrix4D));
}

}
