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

//lights

uniform vec3 lPoint;

out vec3 _color;
out vec2 _TexCoord;

float dot(vec3 a, vec3 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

void main()
{
    gl_Position = PROJECTION * VIEW * CAMERA * MODEL * vec4(aPos, 1.0);

    _TexCoord = aTexCoord;

    _color = vec3(dot(aNormal, lPoint)*0.3 + 0.5);
}