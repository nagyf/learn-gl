//
//  spot-light.hpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 09..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef spot_light_hpp
#define spot_light_hpp

#include <glm/glm.hpp>
#include "light.hpp"

class SpotLight: public Light {
private:
    float constant, linear, quadratic, cutOff, outerCutOff;
    glm::vec3 direction;
public:
    SpotLight(const glm::vec3 &position = glm::vec3(0.0, 0.0, 0.0),
              const glm::vec3 &direction = glm::vec3(0.0, 0.0, 0.0),
              const glm::vec3 &ambient = glm::vec3(0.0, 0.0, 0.0),
              const glm::vec3 &diffuse = glm::vec3(1.0, 1.0, 1.0),
              const glm::vec3 &specular = glm::vec3(1.0, 1.0, 1.0),
              const float constant = 1.0f,
              const float linear = 0.09f,
              const float quadratic = 0.032f,
              const float cutOff = glm::cos(glm::radians(12.5f)),
              const float outerCutOff = glm::cos(glm::radians(15.0f)));
    virtual ~SpotLight();
    
    void setPosition(const glm::vec3 &position);
    void setDirection(const glm::vec3 &direction);
    
    glm::vec3 getDirection() const;
    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;
    float getCutOff() const;
    float getOuterCutOff() const;
};

#endif /* spot_light_hpp */
