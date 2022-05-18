#include "OpenglLayer.h"

OpenglLayer::OpenglLayer(){
}

OpenglLayer::~OpenglLayer(){
    glfwTerminate();
}

void OpenglLayer::onAttach(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // for apple users
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

