#version 430 core

struct LightInfo {
    vec4 cameraPosition; 
    vec4 position;
    vec4 color;    
    int display;
    float ambient;
    float specularFactor; 
    int specularExponent;
};

layout(std140, binding = 1) uniform LightBlock {
    LightInfo light;
};

out vec4 fragColor;

void main() {
    fragColor = light.color;
}
