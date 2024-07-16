#version 460 core

in vec2 TexCoord;
out vec4 fragColor;

uniform sampler2D texture1;

void main()
{
    fragColor =  texture(texture1, TexCoord); // For now, a simple orange color
}
