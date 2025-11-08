#include "shaders.h"
#include <iostream>
#include <fstream>
#include <sstream>

// constructor generates the shader on the fly
// ------------------------------------------------------------------------
void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char *geometrySource)
{
    unsigned int sVertex, sFragment, gShader;
    // Vertex shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    //fragment shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }

    // shader program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, gShader);
    glLinkProgram(this->ID);
    // delete shaders after linking to program
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);

}
// activate the shader
// ------------------------------------------------------------------------
Shader &Shader::Use() 
{ 
    glUseProgram(this->ID); 
    return *this;
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::SetBool(const std::string &name, bool value, bool useShader) 
{           
    if(useShader){
        this->Use();
    } 
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void Shader::SetInt(const std::string &name, int value, bool useShader) 
{ 
    if(useShader){
        this->Use();
    }
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::SetFloat(const std::string &name, float value, bool useShader) 
{ 
    if(useShader){
        this->Use();
    }
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::SetVector2f (const char *name, float x, float y, bool useShader){
    if(useShader){
        this->Use();
    }
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVector2f (const char *name, glm::vec2 &value, bool useShader){
    if(useShader){
        this->Use();
    }
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
// ------------------------------------------------------------------------
void Shader::SetVector3f (const char *name, float x, float y, float z, bool useShader){
    if(useShader){
        this->Use();
    }
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVector3f (const char *name, glm::vec3 &value, bool useShader){
    if(useShader){
        this->Use();
    }
    glUniform3f(glGetUniformLocation(this->ID, name),  value.x, value.y, value.z);
}
// ------------------------------------------------------------------------
void Shader::SetVector4f (const char *name, float x, float y, float z, float w, bool useShader){
    if(useShader){
        this->Use();
    }
    glUniform4f(glGetUniformLocation(this->ID, name),  x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetVector4f (const char *name, glm::vec4 &value, bool useShader){
    if(useShader){
        this->Use();
    }
    glUniform4f(glGetUniformLocation(this->ID, name),  value.x, value.y, value.z, value.w);
}
// ------------------------------------------------------------------------
void Shader::SetMatrix4(const char* name, const glm::mat4 &matrix, bool useShader)
{
    if(useShader){
        this->Use();
    }
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}
// ------------------------------------------------------------------------
// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

