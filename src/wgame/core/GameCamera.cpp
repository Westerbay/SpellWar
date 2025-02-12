/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameCamera.hpp>


namespace wgame {

GameCamera::GameCamera(
    const Point3D & position, 
    const Size & size, 
    float FOVdeg,
    float nearPlane,
    float farPlane
) : position(position), size(size), nearPlane(nearPlane), farPlane(farPlane) {
    _orientation = Vector3D(0.0f, 0.0f, -1.0f);
    _up = Vector3D(0.0f, 1.0f, 0.0f);
    setFOVdeg(FOVdeg);
    update();
}

void GameCamera::setFOVdeg(float FOVdeg) {
    _FOVrad = glm::radians(FOVdeg);
}

void GameCamera::update() {
    Matrix4D view(1.0f);
    Matrix4D projection(1.0f);

    view = glm::lookAt(position, position + _orientation, _up);
    projection = glm::perspective(_FOVrad, (float) (size.width / size.height), nearPlane, farPlane);
    _cameraMatrix = projection * view;    
}

void * GameCamera::getMatrixValuePtr() {
    return glm::value_ptr(_cameraMatrix);
}

}
