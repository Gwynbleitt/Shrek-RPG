#include "Shader.h"

std::string Shader::read_shader(const std::string& path){
    std::string line, tmp = "";
    std::ifstream file;
    file.open( path );
    if(file.is_open()){
        while(getline(file,line)){
            tmp.append(line);
            tmp.append("\n");
        }
       file.close();
    } else printf("FAILED TO READ SHADER\n");
    return tmp;
}

bool Shader::SHADER_ERROR_CHECK(unsigned int id, bool type){
    int success;

    if(type) glGetProgramiv(id, GL_LINK_STATUS, &success);
    else     glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(id, 512, nullptr, log);
        if(type) printf("SHADER PROGRAM LINKING ERROR\n%s\n",log);
        else     printf("SHADER COMPILATION ERROR\n%s\n",log);
    }
    return success ? true : false;
}

Shader::Shader(const std::string& vs_path, const std::string& fs_path){

     
    unsigned int vertexshader, fragmentshader;

    std::string tmp = read_shader(vs_path);
    const char* shadersrc = tmp.c_str();

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &shadersrc, nullptr);
    glCompileShader(vertexshader);

    tmp = read_shader(fs_path);
    shadersrc = tmp.c_str();

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &shadersrc, nullptr);
    glCompileShader(fragmentshader);

    if(!(SHADER_ERROR_CHECK(vertexshader,SHADER)&&SHADER_ERROR_CHECK(fragmentshader,SHADER))) exit(EXIT_FAILURE);

    std::cout << "SHADERS_COMPILED\n";

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexshader);
    glAttachShader(m_ID, fragmentshader);
    glLinkProgram(m_ID);

    if(!SHADER_ERROR_CHECK(m_ID, SHADER_PROGRAM) ) exit(EXIT_FAILURE);
    printf("SHADER_PROGRAM_LINKED\n");

    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

}

void Shader::setmat3(const char* name,  glm::mat3& val)
{
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, false, glm::value_ptr(val));  
}

void Shader::setmat4(const char* name,  glm::mat4& val)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, false, glm::value_ptr(val));
}

void Shader::setfloat(const char* name,  float& val)
{
    glUniform1f(glGetUniformLocation(m_ID, name), val);
}

void Shader::setvec3(const char* name,  glm::vec3& val)
{
    glUniform3fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(val));
}

void Shader::setvec4(const char* name,  glm::vec4& val)
{
    glUniform4fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(val));
}
void Shader::setint1(const char* name, int& val)
{
    glUniform1i(glGetUniformLocation(m_ID, name), val);
}



void Shader::use()
{
    glUseProgram(m_ID);
}

Shader::~Shader(){
    glDeleteProgram(m_ID);

    std::cout << "shader des" << '\n';
}