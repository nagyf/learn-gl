//
//  directional-light.hpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 06..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef directional_light_hpp
#define directional_light_hpp

#include <glm/glm.hpp>
#include "light.hpp"

class DirectionalLight: public Light {
public:
    DirectionalLight(const glm::vec3 &position = glm::vec3(0.0, 0.0, 0.0),
               const glm::vec3 &ambient = glm::vec3(1.0, 1.0, 1.0),
               const glm::vec3 &diffuse = glm::vec3(1.0, 1.0, 1.0),
               const glm::vec3 &specular = glm::vec3(1.0, 1.0, 1.0));
    virtual ~DirectionalLight();
    
    glm::vec3 getDirection() const;
};

#endif /* directional_light_hpp */
