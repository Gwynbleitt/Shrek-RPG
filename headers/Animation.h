#include <glm/glm.hpp>
#include <vector>


struct KeyFrame
{

    float time;

    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
};

class  Animation
{

    std::vector<KeyFrame> m_keyframes;

    void add(KeyFrame key);

};