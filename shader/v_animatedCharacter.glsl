#version 300 es

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normals;
uniform mat4 u_MVP;

out mediump vec3 frag_normals;

void main()
{
    frag_normals = a_Normals;
    gl_Position = u_MVP * vec4(a_Position, 1.0);
}
