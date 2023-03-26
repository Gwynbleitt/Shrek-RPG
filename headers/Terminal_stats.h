#include <iostream>
#include <stdio.h>

class T_Stats
{

    float m_fps;

    unsigned int mn_mesh, mn_model;

public:

    void add_model(int n);
    void add_mesh(int n);

    void update(float& delta_time);
    void render();

    T_Stats();
};