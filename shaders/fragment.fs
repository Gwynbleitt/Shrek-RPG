#version 330 core

out vec4 FragColor;

in vec3 _color;
in vec2 _TexCoord;

//textures

uniform sampler2D ALBEDO;
uniform sampler2D SPECULAR;
uniform sampler2D NORMAL;


void main(){

    FragColor = vec4(_color,1.0) * texture(ALBEDO, _TexCoord);
    //FragColor = vec4(1.0);
}