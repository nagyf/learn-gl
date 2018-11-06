//
//  gl-object.hpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 04..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef gl_object_hpp
#define gl_object_hpp

#include <boost/shared_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader/shader.h"

class GLObject {
protected:
    const GLObject *parent = NULL;
    
    glm::mat4 modelMatrix;
    
    virtual void preRender(const Shader &shader) {};
    virtual void doRender(const Shader &shader) = 0;
    virtual void postRender(const Shader &shader) {};
    
    glm::vec3 axisX() {
        return glm::vec3(1.0, 0.0, 0.0);
    }
    
    glm::vec3 axisY() {
        return glm::vec3(0.0, 1.0, 0.0);
    }
    
    glm::vec3 axisZ() {
        return glm::vec3(0.0, 0.0, 1.0);
    }
    
public:
    GLObject();
    virtual ~GLObject();
    
    void setParent(const GLObject *parent) {
        this->parent = parent;
    }
    
    const GLObject * getParent() const {
        return parent;
    }
    
    void render(const Shader &shader);
    
    virtual void setModelMatrix(const glm::mat4 &mat);
    virtual glm::mat4 getModelMatrix() const;
    
    void rotate(float radians, const glm::vec3 &axes);
    void rotateX(float radians);
    void rotateY(float radians);
    void rotateZ(float radians);
    void rotateXY(float radians);
    void rotateXZ(float radians);
    void rotateYZ(float radians);
};

#endif /* gl_object_hpp */
