#version 420 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D colorSampler;

void main() {
    fragColor = texture(colorSampler, texCoord);
}
