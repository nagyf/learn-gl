#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    // the program ID
    unsigned int ID;
    
    // constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // use/activate the shader
    void use() const;
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type) const;
    int getUniformLocation(const std::string &name) const;
    std::string readShaderFile(const std::string &path) const;
    unsigned int compileShader(const std::string &path, const std::string &type) const;
};

#endif
