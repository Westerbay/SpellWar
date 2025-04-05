#version 430 core

#define BACKGROUND_MODE 0
#define WORLD_MODE 1
#define HUD_MODE 2

struct LightInfo {
    vec4 cameraPosition; 
    vec4 position;
    vec4 color;    
    bool display;
    float defaultAmbient;
    float defaultSpecularFactor; 
    int defaultSpecularExponent;
};

layout(std140, binding = 1) uniform LightBlock {
    LightInfo light;
};

in vec3 fragPosition;
in vec3 fragNormal;
in vec4 color;

out vec4 fragColor;

uniform int drawMode;

void main() {
    if (light.display && drawMode == WORLD_MODE) {
        vec3 normal = normalize(fragNormal);
        vec3 lightDirection = normalize(light.position.xyz - fragPosition);
        float diffuse = max(dot(normal, lightDirection), 0.0);
        
        vec3 viewDirection = normalize(light.cameraPosition.xyz - fragPosition);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), light.defaultSpecularExponent);
        float specular = specAmount * light.defaultSpecularFactor;

        fragColor = color;
        fragColor.xyz = color.xyz * light.color.xyz * (diffuse + light.defaultAmbient + specular);
    } 
    else {
        fragColor = color;
    }
}
