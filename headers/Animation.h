#include <glm/glm.hpp>
#include <vector>


struct keyFrame
{

    float time;

    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
};

class Animator
{
    std::vector<keyFrame> m_KeyFrames;

    void LoadAnimation();
};

