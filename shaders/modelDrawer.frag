#version 430 core

struct LightInfo {
    vec4 position;
    vec4 color;    
};

layout(std140, binding = 1) uniform LightBlock {
    LightInfo light;
};

in vec3 currentPosition;
in vec3 fragNormal;
in vec2 texCoord0;

out vec4 fragColor;

uniform sampler2D textureDiffuse;

void main() {
    if (light.position.w > 0) {
        vec3 lightDirection = normalize(light.position.xyz - currentPosition);
        float diffuse = max(dot(fragNormal, lightDirection), 0.0);
        vec4 color = texture(textureDiffuse, texCoord0);
        color = color * vec4(light.color.xyz, 1.0) * (diffuse + light.color.w);
        color.w = 1;
        fragColor = color;
    } 
    else {
        vec4 color = texture(textureDiffuse, texCoord0);
        color.w = 1;
        fragColor = color;
    }    
}
