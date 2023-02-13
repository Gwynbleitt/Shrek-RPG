#include <glm/glm.hpp>
#include "DS_math.hpp"


class Camera
{

    glm::vec3
    m_position,
    m_origin;

    

public:

    glm::mat4 
    *m_view,
    *m_camera;

    glm::vec3 u,r,t;

    void lookat(glm::vec3& direction);
    void translate(glm::vec3 pos);
    Camera();
    ~Camera();
};