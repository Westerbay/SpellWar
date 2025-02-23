#version 430 core

layout (location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform CameraBlock {
    mat4 cameraMatrix;
};

out vec3 texCoords;

void main() {
    vec4 pos = cameraMatrix * vec4(aPos, 1.0);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    texCoords = vec3(aPos.x, aPos.y, -aPos.z);
}
