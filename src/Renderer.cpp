#include "Renderer.h"

void Renderer::setshader(Shader& shader)
{
    glUseProgram(shader.m_ID);

    m_shader = &shader;
}

Renderer::Renderer(GLFWwindow& win, float FOV, float n, float f,  Shader& shader)
{
    m_near = n;
    m_far = f;
    m_FOV = FOV;
    m_Mprojection = glm::mat4(1.0f);

    m_lPoint = {glm::vec3(0.0f),0.0f};

    setshader(shader);
    
}

void Renderer::fb_u(int w, int h)
{
    glm::projection(m_Mprojection, m_FOV, (float)w/h, m_near, m_far);

    m_shader->setmat4("PROJECTION", m_Mprojection);
}

void Renderer::refresh()
{

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    
}
void Renderer::draw(Model& model, Shader& shader, glm::mat4& view, glm::mat4& camera)
{

    m_shader->setmat4("VIEW", view);
    m_shader->setmat4("CAMERA", camera);
    m_shader->setvec3("lPoint", m_lPoint.Position);
    m_shader->setmat4("MODEL", model.m_Mtransfrom);
    const char* name;

    for(int i = 0; i < model.m_mesh.size(); i++)
    {
        for(int j = 0; j < model.m_mesh[i].m_texture_data.size(); j++)
        {
            glActiveTexture(GL_TEXTURE0+j);
            glBindTexture(GL_TEXTURE_2D, model.m_mesh[i].m_texture_data[j].id);
            m_shader->setint1((model.m_mesh[i].m_texture_data[j].type).c_str(), j);
        }
        
    
        glBindVertexArray(model.m_mesh[i].m_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.m_mesh[i].m_EBO);

        glDrawElements(GL_TRIANGLES, model.m_mesh[i].m_indicies.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
    
}




