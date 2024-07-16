#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 incColorCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord; // Pass the texture coordinates to the fragment shader
void main()
{
    TexCoord = inTexCoord;
    gl_Position = projection * view * model * vec4(inPosition, 1.0f);
}
