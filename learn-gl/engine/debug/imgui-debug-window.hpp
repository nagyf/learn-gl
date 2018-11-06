//
//  imgui-debug-window.hpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 06..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef imgui_debug_window_hpp
#define imgui_debug_window_hpp

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

class ImguiDebugWindow {
private:
    GLFWwindow *glfwWindow;
    void setup();
    ImVec4 clearColor = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);
    
    void showGeneralInformationOverlay();
public:
    ImguiDebugWindow(GLFWwindow *glfwWindow);
    ~ImguiDebugWindow();
    
    void preRender();
    void render();
    void postRender();
};

#endif /* imgui_debug_window_hpp */
