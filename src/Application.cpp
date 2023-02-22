#include "Application.h"

void Application::run()
{

    /* CONSTANT VALUES */
    const float camera_speed = 4.0f;
    const float sensitivity = 0.1f;
    /*------------------*/

    if(!glfwInit()) exit(EXIT_FAILURE);

    GLFWmonitor* monitor;
    const GLFWvidmode* visual;

    monitor = glfwGetPrimaryMonitor();
    if(!monitor) exit(EXIT_FAILURE);
    visual = glfwGetVideoMode(monitor);

    WIN = glfwCreateWindow(visual->width, visual->height, "TEST",  NULL, NULL);
    if(!WIN) exit(EXIT_FAILURE);
    glfwMakeContextCurrent(WIN);
    glfwSetFramebufferSizeCallback(WIN, s_FB_size_callback);
    glfwSetKeyCallback(WIN, s_KEY_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) exit(EXIT_FAILURE);

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_FRONT);

    Model Shrek;



    Shrek.LoadModel("assets/models/Shrek.obj");
    
    //print vertex data

    Shader shader("shaders/vertex.vs", "shaders/fragment.fs");

    glfwSetInputMode(WIN, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    Camera cam1;
    
    Renderer r1 (*WIN, 90, 0.1f, 2.0f, shader);
    glfwSetWindowUserPointer(WIN, &r1);

    glm::vec3 
    direction (0.0f),
    direction2d (0.0f),
    rotation  (0.0f, 0.0f, PI/2);

    glm::vec2 light_rotation(0.0f);
    
    float speed;

    // CURSOR

    double cursor_pos[2];
    double cursor_last[2];
    double cursor_offset[2];

    glfwGetCursorPos(WIN, &cursor_last[0], &cursor_last[1]);
    
    Shrek.m_mesh[0].LoadTexture("assets/textures/Shrek/Albedo.jpg", shader, "ALBEDO", GL_RGB);
    Shrek.m_mesh[0].LoadTexture("assets/textures/Shrek/Roughness.jpg", shader, "SPECULAR", GL_RGB);
    Shrek.m_mesh[0].LoadTexture("assets/textures/Shrek/Normal.jpg", shader, "NORMAL", GL_RGB);

    //EVENT LOOP 

    float current_frame, delta_time = 0.0f, last_frame = 0.0f;

    const float light_speed = 0.02*PI;

    while(!glfwWindowShouldClose(WIN))
    {
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glfwGetCursorPos(WIN, &cursor_pos[0], &cursor_pos[1]);

        cursor_offset[0] = cursor_pos[0]-cursor_last[0];
        cursor_offset[1] = cursor_pos[1]-cursor_last[1];

        cursor_last[0] = cursor_pos[0];
        cursor_last[1] = cursor_pos[1];

        rotation.x += cursor_offset[1] * sensitivity * delta_time;
        rotation.z -= cursor_offset[0] * sensitivity * delta_time;

        speed = camera_speed * delta_time;

        //CAMERA HANDLING

        glm::rotate(direction2d, direction, rotation);

        direction2d = glm::normalize(direction2d);
        
        if(glfwGetKey(WIN, GLFW_KEY_A) == GLFW_PRESS) cam1.translate(-speed*cam1.r); //glm::translate(*(Player.m_Mtransfrom),glm::vec3(-speed,0.f,0.f));
        if(glfwGetKey(WIN, GLFW_KEY_W) == GLFW_PRESS) cam1.translate(-speed*direction); //glm::translate(*(Player.m_Mtransfrom),glm::vec3(0.f,0.f,-speed));
        if(glfwGetKey(WIN, GLFW_KEY_S) == GLFW_PRESS) cam1.translate(speed*direction);  //glm::translate(*(Player.m_Mtransfrom),glm::vec3(0.f,0.f,speed));
        if(glfwGetKey(WIN, GLFW_KEY_D) == GLFW_PRESS) cam1.translate(speed*cam1.r);  //glm::translate(*(Player.m_Mtransfrom),glm::vec3(speed,0.f,0.f));

        //LIGHTS

        if(glfwGetKey(WIN, GLFW_KEY_LEFT) == GLFW_PRESS) light_rotation[1] -= light_speed;
        if(glfwGetKey(WIN, GLFW_KEY_RIGHT) == GLFW_PRESS) light_rotation[1] += light_speed;
        if(glfwGetKey(WIN, GLFW_KEY_DOWN) == GLFW_PRESS) light_rotation[0] -= light_speed;
        if(glfwGetKey(WIN, GLFW_KEY_UP) == GLFW_PRESS) light_rotation[0] += light_speed;

        glm::rotate1(r1.m_lPoint.Position, light_rotation);

        //CAMERA 

        cam1.lookat(direction);
        
        //RENDER 

        r1.refresh();
        
        r1.draw(Shrek, shader, *cam1.m_view, *cam1.m_camera);
        //r1.draw(suzanne, shader, *cam1.m_view, *cam1.m_camera);

        glfwSwapBuffers(WIN);
        glfwPollEvents();
    }
    

}

Application::~Application()
{

    glfwDestroyWindow(WIN);
    glfwTerminate();
    
    std::cout << "closing" << '\n';
}

/* CALLBACKS */

void Application::s_FB_size_callback(GLFWwindow* window, int width, int height)
{
    Renderer* copy = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    
    copy->fb_u(width, height);
  
    glViewport(0, 0, width, height);
}

void Application::s_KEY_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action==1) switch(key){
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            exit(EXIT_FAILURE);
            break;
        default: break;
    }
}
