//
//  directional-light.cpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 06..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include <glm/glm.hpp>
#include "directional-light.hpp"

DirectionalLight::DirectionalLight(const glm::vec3 &position,
                 const glm::vec3 &ambient,
                 const glm::vec3 &diffuse,
                 const glm::vec3 &specular): Light(position, ambient, diffuse, specular) {
}

DirectionalLight::~DirectionalLight() {
}

glm::vec3 DirectionalLight::getDirection() const {
    return -glm::normalize(position);
}
