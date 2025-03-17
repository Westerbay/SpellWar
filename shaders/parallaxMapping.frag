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

in vec3 fragPos;
in vec2 texCoord;
in vec3 tangentLightPos;
in vec3 tangentViewPos;
in vec3 tangentFragPos;

out vec4 fragColor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float heightScale;

void main() {
    if (light.display != 0) {
        vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
        vec2 parallaxTexCoord = ParallaxMapping(texCoord,  viewDir);
        
        vec3 normal = texture(normalMap, parallaxTexCoord).rgb;
        normal = normalize(normal * 2.0 - 1.0);

        vec3 lightDirection = normalize(tangentLightPos - tangentFragPos);
        float diffuse = max(dot(normal, lightDirection), 0.0);
        
        vec3 viewDirection = normalize(tangentViewPos - tangentFragPos);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), light.specularExponent);
        float specular = specAmount * light.specularFactor;

        vec4 color = texture(diffuseMap, parallaxTexCoord);
        color.xyz = color.xyz * light.color.xyz * (diffuse + light.ambient + specular);
        fragColor = color;
    } 
    else {
        vec4 color = texture(diffuseMap, texCoord);
        fragColor = color;
    }
}
