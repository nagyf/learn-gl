//
//  camera.hpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 04..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class FPSCamera {
private:
    glm::vec3 position, worldUp, right, up, front;
    float yaw, pitch;
    float movementSpeed = SPEED;
    float mouseSensitivity = SENSITIVITY;
protected:
    void updateCameraVectors();
public:
    float zoom = ZOOM;
    FPSCamera(const glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           const float yaw = YAW,
           const float pitch = PITCH);
    
    glm::mat4 viewMatrix() const;
    
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);
    
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
};

#endif /* camera_hpp */
