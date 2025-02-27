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

in vec3 currentPosition;
in vec3 fragNormal;
in vec3 color;

out vec4 fragColor;

void main() {
    if (light.display != 0) {
        vec3 normal = normalize(fragNormal);
        vec3 lightDirection = normalize(light.position.xyz - currentPosition);
        float diffuse = max(dot(normal, lightDirection), 0.0);
        
        vec3 viewDirection = normalize(light.cameraPosition.xyz - currentPosition);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), light.specularExponent);
        float specular = specAmount * light.specularFactor;

        fragColor = vec4(color, 1.0f);
        fragColor.xyz = color * light.color.xyz * (diffuse + light.ambient + specular);
    } 
    else {
        fragColor = vec4(color, 1.0f);
    }
}
