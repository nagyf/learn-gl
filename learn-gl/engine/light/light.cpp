//
//  light.cpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 05..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include <glm/glm.hpp>
#include "light.hpp"

Light::Light(const glm::vec3 &position,
             const glm::vec3 &ambient,
             const glm::vec3 &diffuse,
             const glm::vec3 &specular) {
    setPosition(position);
    setAmbient(ambient);
    setDiffuse(diffuse);
    setSpecular(specular);
}

Light::~Light() {
}

void Light::setPosition(const glm::vec3 &position) {
    this->position = glm::vec3(position);
}

glm::vec3 Light::getPosition() const {
    return glm::vec3(position);
}

void Light::setAmbient(const glm::vec3 &ambient) {
    this->ambient = glm::vec3(ambient);
}

glm::vec3 Light::getAmbient() const {
    return glm::vec3(ambient);
}

void Light::setDiffuse(const glm::vec3 &diffuse) {
    this->diffuse = glm::vec3(diffuse);
}

glm::vec3 Light::getDiffuse() const {
    return glm::vec3(diffuse);
}

void Light::setSpecular(const glm::vec3 &specular) {
    this->specular = glm::vec3(specular);
}

glm::vec3 Light::getSpecular() const {
    return glm::vec3(specular);
}
