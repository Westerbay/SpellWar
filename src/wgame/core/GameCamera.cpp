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
    _matrices = {Matrix4D(1.0f), Matrix4D(1.0f)};
    _ubo.configure(sizeof(CameraMatrices));
    _ubo.setBindingPoint(CAMERA_MATRICES_POINT);
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

void GameCamera::apply() const {
    _ubo.setData(&_matrices, sizeof(CameraMatrices));
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
        (float) hitbox.size.x / hitbox.size.y,
         _nearPlane, 
         _farPlane
    );
    Matrix4D view = glm::lookAt(position, position + orientation[2], orientation[1]);
    
    _matrices.cameraMatrixDynamic = projection * view;
    _matrices.cameraMatrixStatic = projection * Matrix4D(Matrix3D(view));
}

}
