//
//  light.hpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 05..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef light_hpp
#define light_hpp

#include <glm/glm.hpp>

class Light {
protected:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
public:
    Light(const glm::vec3 &position = glm::vec3(0.0, 0.0, 0.0),
          const glm::vec3 &ambient = glm::vec3(1.0, 1.0, 1.0),
          const glm::vec3 &diffuse = glm::vec3(1.0, 1.0, 1.0),
          const glm::vec3 &specular = glm::vec3(1.0, 1.0, 1.0));
    virtual ~Light();
    
    void setPosition(const glm::vec3 &position);
    glm::vec3 getPosition() const;
    
    void setAmbient(const glm::vec3 &ambient);
    glm::vec3 getAmbient() const;
    
    void setDiffuse(const glm::vec3 &diffuse);
    glm::vec3 getDiffuse() const;
    
    void setSpecular(const glm::vec3 &specular);
    glm::vec3 getSpecular() const;
};

#endif /* light_hpp */
