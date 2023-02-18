#version 330 core

in vec3 frag_normals;
out vec4 fragColor;

void main()
{
    fragColor = vec4(frag_normals * 0.5 + 0.5, 1.0); //vec4(normals * 0.5 + 0.5, 1.0);
}
