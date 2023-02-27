#version 300 es

in mediump vec3 frag_normals;
out mediump vec4 fragColor;

void main()
{
    fragColor = vec4(frag_normals * 0.5 + 0.5, 1.0); //vec4(normals * 0.5 + 0.5, 1.0);
}
