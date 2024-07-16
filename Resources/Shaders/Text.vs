#version 460 core

layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 FragTextCoords;

uniform mat4 ProjectionMat;

void main()
{ 
    gl_Position = ProjectionMat * vec4(vertex.xy, 0.0, 1.0);
    FragTextCoords = vertex.zw;
    }