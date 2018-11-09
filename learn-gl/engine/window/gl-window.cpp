//
//  gl-window.cpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 04..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gl-window.hpp"

GLWindow::GLWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    this->width = mode->width;
    this->height = mode->height;
    window = glfwCreateWindow(mode->width, mode->height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, cursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    
    glfwSetErrorCallback([](int /* error */, const char *description) {
        std::cerr << description << '\n';
        throw std::runtime_error(description);
    });
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    viewportDidResize(width, height);
    
    glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
}

GLWindow::~GLWindow() {
    glfwTerminate();
}

void GLWindow::viewportDidResize(const unsigned int width, const unsigned int height) {
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);
    projectionMatrix = createProjectionMatrix(45.0f, width, height);
}

glm::mat4 GLWindow::createProjectionMatrix(const float zoom, const unsigned int width, const unsigned int height) const {
    return glm::perspective(glm::radians(zoom), (float)width/(float)height, 0.1f, 100.0f);
}

void GLWindow::preRun() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void GLWindow::postRun() {
}

void GLWindow::preRender() {
}

void GLWindow::postRender() {
}

int GLWindow::run() {
    preRun();
    
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        preRender();
        render();
        postRender();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    postRun();
    return 0;
}

void GLWindow::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void GLWindow::mouseMoved(const double x, const double y) {
}

void GLWindow::mouseScrolled(const double xOffset, const double yOffset) {
}
