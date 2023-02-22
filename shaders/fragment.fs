#version 330 core

out vec4 FragColor;

in vec3 _Normal;
in vec2 _TexCoord;
in vec3 _Camera;

//textures

uniform sampler2D ALBEDO;
uniform sampler2D SPECULAR;
uniform sampler2D NORMAL;

//lights

uniform vec3 lPoint;

//MATERIAL SETTINGS

float shine;

float dot(vec4 a, vec4 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


void main(){

    float light = dot(vec4(lPoint, 1.0), vec4(_Normal, 1.0));// * normalize(texture(NORMAL, _TexCoord)));
    shine = 5.0;

    //FragColor = texture(ALBEDO, _TexCoord) * ((light*0.3)+0.5);// + ((1.0-texture(SPECULAR, _TexCoord)) * pow(light, shine));
    FragColor = texture(ALBEDO, _TexCoord) * light + pow(light, 21);
    
    //QUICK VIEW

    //vec4 quickview =  texture(SPECULAR, _TexCoord);

//    FragColor = vec4(vec3(((light*0.3)+0.5)), 1.0);
    
}