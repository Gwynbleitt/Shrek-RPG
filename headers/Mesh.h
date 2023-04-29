#include "vertex.h"
#include "texture.h"
#include "Shader.h"

#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>




class Mesh
{
public:

    std::vector<Vertex> m_verex_data;
    std::vector<Texture> m_texture_data;
    std::vector<unsigned int> m_indicies;

    glm::mat4 m_Mtransfrom;
    
    unsigned int m_VAO, m_EBO, m_VBO;

    //generates texture from file using STB library
    void LoadTexture(const char* path, unsigned int type, unsigned int colors);

    //1. construct mesh object based on vertrx data, index data and usage. Sets up all necessery buffers
    Mesh(std::vector<Vertex> &verticies, std::vector<unsigned int> &indicies, int Usage, bool Vertex_flags[2]);
    //2. copy operator
    Mesh(const Mesh& tmp); 
    ~Mesh();
  

};