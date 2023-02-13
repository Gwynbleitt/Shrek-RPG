#include "vertex.h"
#include "texture.h"
#include "Shader.h"

#include <vector>
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb_image.h"


class Mesh
{
public:

    std::vector<Vertex> m_verex_data;
    std::vector<Texture> m_texture_data;
    std::vector<unsigned int> m_indicies;
    
    unsigned int m_VAO, m_EBO, m_VBO;

    //generates texture from file using STB library
    void LoadTexture(const char* path, Shader& shader, const char* type, unsigned int colors);

    //construct mesh object based on vertrx data, index data and usage. Sets up all necessery buffers
    Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, int Usage, bool Vertex_flags[2]);


};