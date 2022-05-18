#include "ImguiLayer.h"

ImguiLayer::ImguiLayer(GLFWwindow *win) : 
    m_win{win}{

}

ImguiLayer::~ImguiLayer(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void ImguiLayer::begin(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


}

void ImguiLayer::end(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLayer::onAttach(){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_win, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}
