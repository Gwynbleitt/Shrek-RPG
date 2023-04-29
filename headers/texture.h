#include <iostream>
#include "glad/glad.h"
#include "stb_image.h"

#define ALBEDO 0
#define SPECULAR 1
#define NORMAL 2

struct Texture
{
    unsigned int id;
    unsigned int type;

    Texture(unsigned int T, const char* path, unsigned int colors);
    Texture(Texture&& move);
   
    ~Texture();
};