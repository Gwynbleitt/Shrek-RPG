#include "Mesh.h"

class Weapon : public Mesh
{

    std::string m_name;

    float m_Damage, m_Weight;
};

namespace Weapons
{

    class Sword : public Weapon
    {

    };

    class Axe : public Weapon
    {

    };


};