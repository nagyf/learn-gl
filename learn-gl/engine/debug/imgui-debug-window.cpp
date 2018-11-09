//
//  imgui-debug-window.cpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 06..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "imgui-debug-window.hpp"

ImguiDebugWindow::ImguiDebugWindow(GLFWwindow *glfwWindow) {
    this->glfwWindow = glfwWindow;
    setup();
}

ImguiDebugWindow::~ImguiDebugWindow() {
    ImGui::DestroyContext();
}

void ImguiDebugWindow::setup() {
    const char* glsl_version = "#version 330";
    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();
}

void ImguiDebugWindow::preRender() {
}

void ImguiDebugWindow::render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    //ImGui::ShowDemoWindow();
    
    showGeneralInformationOverlay();

    ImGui::Render();
}

void ImguiDebugWindow::showGeneralInformationOverlay() {
    const float DISTANCE = 10.0f;
    static int corner = 1;
    ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
    ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.3f);
    ImGuiWindowFlags configuration = ImGuiWindowFlags_NoMove
    | ImGuiWindowFlags_NoTitleBar
    | ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_AlwaysAutoResize
    | ImGuiWindowFlags_NoSavedSettings
    | ImGuiWindowFlags_NoFocusOnAppearing
    | ImGuiWindowFlags_NoNav;
    
    if (ImGui::Begin("Example: Simple Overlay", NULL, configuration)) {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Separator();
        if (ImGui::IsMousePosValid()) {
            ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
        } else {
            ImGui::Text("Mouse Position: <invalid>");
        }
        ImGui::Separator();
        if(ImGui::ColorEdit3("Clear color", (float*)&clearColor)) {
            glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        }
    }
    ImGui::End();
}

void ImguiDebugWindow::postRender() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
