#version 330 core

// '_' in out varibles

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTexCoord;

//matricies

uniform mat4 MODEL;
uniform mat4 PROJECTION;
uniform mat4 VIEW;
uniform mat4 CAMERA;

out vec3 _Normal;
out vec2 _TexCoord;
out vec3 _Camera;

void main()
{
    gl_Position = PROJECTION * VIEW * CAMERA * MODEL * vec4(aPos, 1.0);

    _TexCoord = aTexCoord;
    _Normal = aNormal;
    _Camera = normalize(vec3(CAMERA[3][0], CAMERA[3][1], CAMERA[3][2]));
}