#ifndef WINDOW_H
#define WINDOW_H

#include "../OpenGL/OpenglBuild.h"
#include <string>
#include <iostream>


class Window{
    public:
        Window(const std::string& label, uint32_t width, uint32_t height);
        ~Window();

        GLFWwindow** getContext();
        uint32_t getWidth();
        uint32_t getHeight();
        void update();
        bool isOpen();
    
    private:
        GLFWwindow* m_winID;
        const std::string& m_label;
        uint32_t m_width;
        uint32_t m_height;
};

#endif