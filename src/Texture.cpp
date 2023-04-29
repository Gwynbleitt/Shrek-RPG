#include "texture.h"

Texture::Texture(unsigned int T, const char* path, unsigned int colors)
{
    
    printf("Texture move\n");

    type = T;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    int width, height, channels;

    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if(!data) exit(EXIT_FAILURE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colors, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    
}


Texture::Texture(Texture&& move)
{
    printf("Texture move\n");
    id = move.id;
    type = move.type;
    move.id = 0;
}

Texture::~Texture()
{
   printf("Destructor::tex");
   if(id!=0) glDeleteTextures(1, &id);
}

