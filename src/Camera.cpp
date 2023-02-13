#include "Camera.h"

Camera::Camera()
{
    m_view = new glm::mat4(1.0f);
    m_camera = new glm::mat4(1.0f);
}

Camera::~Camera()
{
    delete m_view;
    delete m_camera;
}

void Camera::translate(glm::vec3 pos)
{
    //m_position = POS;
    glm::translate(*m_camera, pos);
}

void Camera::lookat(glm::vec3& direction)
{
    t = glm::normalize(direction);
    r = glm::normalize(glm::cross(t, glm::vec3(0.0f,1.0f,0.0f)));
    u = glm::normalize(glm::cross(r, t));

    (*m_view)[0] = glm::vec4(r.x, u.x, t.x, 0.0f);
    (*m_view)[1] = glm::vec4(r.y, u.y, t.y, 0.0f);
    (*m_view)[2] = glm::vec4(r.z, u.z, t.z, 0.0f);
}