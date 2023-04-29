#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &verticies, std::vector<unsigned int> &indicies, int Usage,  bool Vertex_flags[2])
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
    //assuming vertex flag = 1,1 (to fix)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24);
    glEnableVertexAttribArray(2);
    

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    m_Mtransfrom = glm::mat4(1.0f);

}
//correct copying behavior
Mesh::Mesh(const Mesh& tmp)
{
    m_verex_data = tmp.m_verex_data;
    m_indicies = tmp.m_indicies;
    m_Mtransfrom = tmp.m_Mtransfrom;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_verex_data.size() * sizeof(Vertex), &m_verex_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(unsigned int), &m_indicies[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    //assuming vertex flag = 1,1
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
    glEnableVertexAttribArray(1);
  
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);


}

Mesh::~Mesh()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
 
    if(m_VBO) glDeleteBuffers(1, &(m_VBO));
    if(m_EBO) glDeleteBuffers(1, &(m_EBO));
    if(m_VAO) glDeleteVertexArrays(1, &(m_VAO));

    std::cout << "MESH DESTRUCTOR" << '\n';
}

void Mesh::LoadTexture(const char* path, unsigned int type, unsigned int colors)
{
    
    m_texture_data.push_back(Texture(type, path, colors));

}

