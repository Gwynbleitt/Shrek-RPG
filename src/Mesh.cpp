#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, int Usage,  bool Vertex_flags[2])
{

    m_verex_data = verticies;
    m_indicies = indicies;
    
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    if(Vertex_flags[0])
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
        glEnableVertexAttribArray(1);
    }
    if(Vertex_flags[1])
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24);
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

}



void Mesh::LoadTexture(const char* path, Shader& shader, const char* type, unsigned int colors)
{

    Texture tmp;

    glGenTextures(1, &tmp.id);
    glBindTexture(GL_TEXTURE_2D, tmp.id);

    tmp.type = type;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    int width, height, channels;

    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if(!data) exit(EXIT_FAILURE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colors, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
     
    m_texture_data.push_back(tmp);

    stbi_image_free(data);


}