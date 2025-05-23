#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 mvpMatrix;

void main()
{
    gl_Position = mvpMatrix * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
    // color = vec4(0.0, 1.0, 0.0, 1.0);
}
