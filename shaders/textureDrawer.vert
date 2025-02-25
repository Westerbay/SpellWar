#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 3) in vec2 aTexCoord0;

out vec2 texCoord;

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

void main() {
    gl_Position = cameraMatrixDynamic * vec4(aPos, 1.0);
    texCoord = aTexCoord0;
}
