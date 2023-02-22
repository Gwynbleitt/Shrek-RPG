#include "Model.h"

class Character
{

public:

    std::string m_name;

    float m_HP, m_Stamina;

    //Stats

    unsigned int
    m_Level,
    m_Str,
    m_Dex;

    float m_speed;
    //Sword -> sDMG * Dex
    //Axe -> aDMG * Str
    float Damage; 

    Character(std::string name);
    ~Character();
};