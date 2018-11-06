//
//  point-light.hpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 05..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef point_light_hpp
#define point_light_hpp

#include "light.hpp"

class PointLight: public Light {
public:
    PointLight(const glm::vec3 &position = glm::vec3(0.0, 0.0, 0.0),
               const glm::vec3 &ambient = glm::vec3(1.0, 1.0, 1.0),
               const glm::vec3 &diffuse = glm::vec3(1.0, 1.0, 1.0),
               const glm::vec3 &specular = glm::vec3(1.0, 1.0, 1.0));
    virtual ~PointLight();
};

#endif /* point_light_hpp */
