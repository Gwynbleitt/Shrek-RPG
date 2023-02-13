#ifndef SHADER_H
#define SHADER_H

#define SHADER 0
#define SHADER_PROGRAM 1
#define GL_GLEXT_PROTOTYPES

#include  "glad/glad.h"
#include  <GLFW/glfw3.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <cstring>
#include  <iostream>
#include  <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    
    bool  SHADER_ERROR_CHECK (unsigned int shaderid, bool type);
    std::string read_shader(const std::string& path);

    char log[512];

public:

    unsigned int m_ID;

    //use shader program
    void use(),

    setmat4(const char* name, glm::mat4& val),
    setmat3(const char* name, glm::mat3& val),
    setvec3(const char* name, glm::vec3& val),
    setvec4(const char* name, glm::vec4& val),
    setint1(const char* name, int& val),
    setfloat(const char* name, float& val);


    Shader(const std::string& vs_path, const std::string& fs_path);
    ~Shader();

};

#endif