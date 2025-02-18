#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 3) in vec2 aTexCoord0;

out vec2 texCoord;

layout(std140, binding = 0) uniform CameraBlock {
    mat4 cameraMatrix;
};

void main() {
    gl_Position = cameraMatrix * vec4(aPos, 1.0);
    texCoord = aTexCoord0;
}
