#version 430 core

layout(location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

uniform mat4 model;

void main() {
    gl_Position = cameraMatrixStatic * model * vec4(aPos, 1.0);
}
