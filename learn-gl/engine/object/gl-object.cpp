//
//  gl-object.cpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 04..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include "gl-object.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLObject::GLObject() {
    modelMatrix = glm::identity<glm::mat4>();
}

GLObject::~GLObject() {
}

void GLObject::setModelMatrix(const glm::mat4 &mat) {
    modelMatrix = glm::mat4(mat);
}

glm::mat4 GLObject::getModelMatrix() const {
    if(parent) {
        return glm::mat4(parent->getModelMatrix() * modelMatrix);
    } else {
        return glm::mat4(modelMatrix);
    }
}

void GLObject::rotate(float radians, const glm::vec3 &axes) {
    setModelMatrix(glm::rotate(modelMatrix, glm::radians(radians), axes));
}

void GLObject::rotateX(float radians) {
    setModelMatrix(glm::rotate(modelMatrix, glm::radians(radians), axisX()));
}

void GLObject::rotateY(float radians) {
    setModelMatrix(glm::rotate(modelMatrix, glm::radians(radians), axisY()));
}

void GLObject::rotateZ(float radians) {
    setModelMatrix(glm::rotate(modelMatrix, glm::radians(radians), axisZ()));
}

void GLObject::rotateXY(float radians) {
    setModelMatrix(glm::rotate(modelMatrix, glm::radians(radians), axisX() + axisY()));
}

void GLObject::rotateXZ(float radians) {
    setModelMatrix(glm::rotate(modelMatrix, glm::radians(radians), axisX() + axisZ()));
}

void GLObject::rotateYZ(float radians) {
    setModelMatrix(glm::rotate(modelMatrix, glm::radians(radians), axisY() + axisZ()));
}

void GLObject::moveY(float dy) {
    setModelMatrix(glm::translate(modelMatrix, glm::vec3(0.0f, dy, 0.0f)));
}

void GLObject::render(const Shader &shader) {
    shader.use();
    preRender(shader);
    
    shader.setMat4("model", getModelMatrix());
    doRender(shader);
    
    postRender(shader);
}
