#ifndef SHADERS_H
#define SHADERS_H

#include <string>

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor
    Shader() { }
    // sets the current shader as active
    Shader &Use();
    // compiles the shader from given source code
    void Compile(const char* vertexPath, const char* fragmentPath, const char *geometrySource = nullptr);
    // utility uniform functions
    void SetBool(const std::string &name, bool value, bool useShader = false);  
    void SetInt(const std::string &name, int value, bool useShader = false);   
    void SetFloat(const std::string &name, float value, bool useShader = false);
    void SetVector2f (const char *name, float x, float y, bool useShader = false);
    void SetVector2f (const char *name, glm::vec2 &value, bool useShader = false);
    void SetVector3f (const char *name, float x, float y, float z, bool useShader = false);
    void SetVector3f (const char *name, glm::vec3 &value, bool useShader = false);
    void SetVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
    void SetVector4f (const char *name, glm::vec4 &value, bool useShader = false);
    void SetMatrix4(const char* name, const glm::mat4 &matrix, bool useShader = false);
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
  
#endif