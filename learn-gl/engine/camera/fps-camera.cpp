//
//  camera.cpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 04..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "fps-camera.hpp"

FPSCamera::FPSCamera(const glm::vec3 position, const glm::vec3 worldUp, const float yaw, const float pitch) {
    this->position = position;
    this->worldUp = worldUp;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

void FPSCamera::updateCameraVectors() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

glm::mat4 FPSCamera::viewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void FPSCamera::processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    if (direction == UP)
        position += up * velocity;
    if (direction == DOWN)
        position -= up * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void FPSCamera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;
    
    yaw   += xoffset;
    pitch += yoffset;
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    
    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void FPSCamera::processMouseScroll(float yoffset) {
    if (zoom >= 1.0f && zoom <= 45.0f){
        zoom -= yoffset;
    }
    
    if (zoom <= 1.0f){
        zoom = 1.0f;
    }
        
    if (zoom >= 45.0f) {
        zoom = 45.0f;
    }
}

glm::vec3 FPSCamera::getPosition() const {
    return position;
}
