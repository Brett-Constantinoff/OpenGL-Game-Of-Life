#include "Window.h"

Window::Window(const std::string& label, uint32_t width, uint32_t height) : 
    m_label{label}, m_width{width}, m_height{height}{
    m_winID = glfwCreateWindow(m_width, m_height, m_label.c_str(), NULL, NULL);
    if(!m_winID){
        std::cout << "ERROR CREATING OPENGL WINDOW!" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_winID);
    glViewport(0, 0, m_width, m_height);

    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        std::cout << "ERROR INITIALIZING GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

}

Window::~Window(){
    glfwDestroyWindow(m_winID);
}

GLFWwindow** Window::getContext(){
    return &m_winID;
}

uint32_t Window::getWidth(){
    return m_width;
}

uint32_t Window::getHeight(){
    return m_height;
}

bool Window::isOpen(){
    bool result = !glfwWindowShouldClose(m_winID);
    return result;
}

void Window::update(){
    glfwSwapBuffers(m_winID);
    glfwPollEvents();
}