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
                       const glm::vec3 &specular): Light(position, ambient, diffuse, specular) {
}

PointLight::~PointLight() {
}
