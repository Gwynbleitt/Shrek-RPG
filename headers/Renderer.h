#include "Model.h"
#include "Camera.h"
#include <DS_math.hpp>
#include "Lights.h"

class Renderer
{

    glm::mat4* m_Mprojection;
    
    float m_near, m_far, m_FOV;

    Shader* m_shader;

public:
        
    lPoint m_lPoint;

    //updates projection matrix on framebuffer size change
    void fb_u(int w, int h);
    //clears buffers
    void refresh();
    //draws all meshes of given model
    void draw(Model& model, Shader& shader, glm::mat4& view, glm::mat4& camera);

    //sets current shader program and reassignes m_shader pointer
    void setshader(Shader& shader);

    Renderer(GLFWwindow& win, float FOV, float n, float f, Shader& shader);
    ~Renderer();

};