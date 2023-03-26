#include "Terminal_stats.h"

T_Stats::T_Stats()
{
    mn_mesh = 0;
    mn_model = 0;
}

void T_Stats::update(float& delta_time)
{
    m_fps = 60.0/delta_time;
}

void T_Stats::add_model(int n)
{
    mn_model += n;
}

void T_Stats::add_mesh(int n)
{
    mn_mesh += n;
}

void T_Stats::render()
{
    system("clear");

    printf("fps: %f \n", m_fps);
    printf("models: %u \n", mn_model);
    printf("meshes: %u \n", mn_mesh);
}