#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

out vec3 currentPosition;
out vec3 fragNormal;
out vec3 color;

uniform mat4 model;

void main() {
    gl_Position = cameraMatrixDynamic * model * vec4(aPos, 1.0);
    color = aColor;
    fragNormal = vec3(transpose(inverse(model)) * vec4(aNormal, 1.0));
    currentPosition = vec3(model * vec4(aPos, 1.0));
}
