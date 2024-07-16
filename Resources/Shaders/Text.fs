#version 460 core

in vec2 FragTextCoords;


uniform sampler2D TextTexture;
uniform vec3 TextColor;

out vec4 FinalColor;

void main()
{ 
  float Alpha = texture(TextTexture, FragTextCoords).r;
    FinalColor = vec4(TextColor, Alpha);
}