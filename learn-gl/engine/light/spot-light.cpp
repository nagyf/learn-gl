//
//  spot-light.cpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 09..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include "spot-light.hpp"

SpotLight::SpotLight(const glm::vec3 &position,
                     const glm::vec3 &direction,
                     const glm::vec3 &ambient,
                     const glm::vec3 &diffuse,
                     const glm::vec3 &specular,
                     const float constant,
                     const float linear,
                     const float quadratic,
                     const float cutOff,
                     const float outerCutOff): Light(position, ambient, diffuse, specular) {
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;
    this->direction = direction;
}

SpotLight::~SpotLight() {
}

float SpotLight::getConstant() const {
    return constant;
}

float SpotLight::getLinear() const {
    return linear;
}

float SpotLight::getQuadratic() const {
    return quadratic;
}

float SpotLight::getCutOff() const {
    return cutOff;
}

float SpotLight::getOuterCutOff() const {
    return outerCutOff;
}

void SpotLight::setPosition(const glm::vec3 &position) {
    this->position = position;
}

void SpotLight::setDirection(const glm::vec3 &direction) {
    this->direction = direction;
}

glm::vec3 SpotLight::getDirection() const {
    return direction;
}
