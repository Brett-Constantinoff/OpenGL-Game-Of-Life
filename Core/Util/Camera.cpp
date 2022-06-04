#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed): 
    m_position{position}, m_front{front}, m_up{up}, m_speed{speed}{
};

void Camera::move(GLFWwindow **win, float dt){
    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(m_front);


    const float cameraSpeed = m_speed * dt;

    if (glfwGetKey(*win, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_position += cameraSpeed * m_front;
    }
    if (glfwGetKey(*win, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_position -= cameraSpeed * m_front;
    }
    if (glfwGetKey(*win, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
    }
    if (glfwGetKey(*win, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_position += glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
    }
    if (glfwGetKey(*win, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        m_yaw += 2.0f;
    }
    if (glfwGetKey(*win, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        m_yaw -= 2.0f;
    }
    if (glfwGetKey(*win, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_pitch += 2.0f;
    }
    if (glfwGetKey(*win, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_pitch -= 2.0f;
    }
}

glm::vec3* Camera::getPos(){
    return &m_position;
}

glm::vec3* Camera::getFront(){
    return &m_front;
}

glm::mat4 *Camera::getView(){
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    return &m_view;
}