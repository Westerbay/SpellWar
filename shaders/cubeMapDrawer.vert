#version 430 core

layout (location = 0) in vec3 aPos;

struct CameraMatrices {
    mat4 background;
    mat4 world;   
    mat4 HUD; 
};

layout(std140, binding = 0) uniform CameraBlock {
    CameraMatrices cameraMatrices;
};

out vec3 texCoords;

void main() {
    vec4 pos = cameraMatrices.background * vec4(aPos, 1.0);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    texCoords = vec3(aPos.x, aPos.y, -aPos.z);
}
