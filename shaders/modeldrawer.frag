#version 420 core

in vec2 texCoord0;
in vec2 texCoord1;

out vec4 fragColor;

uniform sampler2D textureDiffuse;
uniform sampler2D textureAO;

void main() {
    vec4 color = texture(textureDiffuse, texCoord0);
    float ao = texture(textureAO, texCoord1).r;
    fragColor = color;
}
