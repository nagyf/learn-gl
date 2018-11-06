//
//  gl-window.hpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 04..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef gl_window_hpp
#define gl_window_hpp

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GLWindow {
private:
    inline static auto WindowResizeCallback(
                                            GLFWwindow *win,
                                            int w,
                                            int h) -> void {
        GLWindow *window = static_cast<GLWindow*>(glfwGetWindowUserPointer(win));
        window->viewportDidResize(w, h);
    }
    
    inline static auto MouseCallback(
                                            GLFWwindow *win,
                                            double x,
                                            double y) -> void {
        GLWindow *window = static_cast<GLWindow*>(glfwGetWindowUserPointer(win));
        window->mouseMoved(x, y);
    }
    
    inline static auto ScrollCallback(
                                            GLFWwindow *win,
                                            double xOffset,
                                            double yOffset) -> void {
        GLWindow *window = static_cast<GLWindow*>(glfwGetWindowUserPointer(win));
        window->mouseScrolled(xOffset, yOffset);
    }
protected:
    unsigned int width, height;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::mat4 projectionMatrix;
    
    GLFWwindow* window;
    
    void viewportDidResize(const unsigned int width, const unsigned int height);
    glm::mat4 createProjectionMatrix(const float zoom, const unsigned int width, const unsigned int height) const;
    virtual void preRun();
    virtual void postRun();
    
    virtual void preRender();
    virtual void postRender();
    
    virtual void render() = 0;
    
    virtual void processInput();
    virtual void mouseMoved(const double x, const double y);
    virtual void mouseScrolled(const double xOffset, const double yOffset);
public:
    GLWindow(const unsigned int width, const unsigned int height);
    virtual ~GLWindow();
    int run();
};

#endif /* gl_window_hpp */
