//
//  point-light.cpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 05..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//


#include "point-light.hpp"

PointLight::PointLight(const glm::vec3 &position,
                       const glm::vec3 &ambient,
                       const glm::vec3 &diffuse,
                       const glm::vec3 &specular,
                       const float constant,
                       const float linear,
                       const float quadratic): Light(position, ambient, diffuse, specular) {
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

PointLight::~PointLight() {
}

float PointLight::getConstant() const {
    return constant;
}

float PointLight::getLinear() const {
    return linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}
