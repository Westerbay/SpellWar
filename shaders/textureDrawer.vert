#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord0;

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

out vec3 currentPosition;
out vec3 fragNormal;
out vec2 texCoord;

void main() {
    gl_Position = cameraMatrixDynamic * vec4(aPos, 1.0);
    texCoord = aTexCoord0;
    fragNormal = aNormal;
    currentPosition = aPos;
}
