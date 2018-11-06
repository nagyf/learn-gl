#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    unsigned int vertex = compileShader(vertexPath, "VERTEX");
    unsigned int fragment = compileShader(fragmentPath, "FRAGMENT");
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string Shader::readShaderFile(const std::string &path) const {
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        std::string content(std::istreambuf_iterator<char>(shaderFile), (std::istreambuf_iterator<char>()));
        return content;
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    }
}

unsigned int Shader::compileShader(const std::string &path, const std::string &type) const {
    const std::string codeStr = readShaderFile(path);
    const GLchar* code = (const GLchar *) codeStr.c_str();
    unsigned int shader;
    if(type == "VERTEX") {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == "FRAGMENT") {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    } else {
        throw std::runtime_error("Unknown shader type: " + type);
    }
    
    if(!shader) {
        throw std::runtime_error("Was unable to create shader object");
    }
    
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader, type);
    
    return shader;
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(getUniformLocation(name), value);
}
    
void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
   glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

int Shader::getUniformLocation(const std::string &name) const {
    unsigned int uniformLocation = glGetUniformLocation(ID, name.c_str());
    if(uniformLocation == -1) {
        std::cerr << "Could not get uniform location: " << name << std::endl;
        throw std::runtime_error("Could not get uniform location: " + name);
    }
    return uniformLocation;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) const {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
            throw std::runtime_error("ERROR::SHADER_COMPILATION_ERROR of type: " + type);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
            throw std::runtime_error("ERROR::PROGRAM_LINKING_ERROR of type: " + type);
        }
    }
}
