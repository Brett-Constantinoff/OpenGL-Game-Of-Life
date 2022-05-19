#ifndef CAMERA_H
#define CAMERA_H

#include "../Libs/glm/glm.hpp"
#include "../Libs/glm/gtc/matrix_transform.hpp"
#include "../Libs/glm/gtc/type_ptr.hpp"
#include "../Src/OpenGL/OpenglBuild.h"

class Camera{
    public:
        Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed);
        void move(GLFWwindow **win, float dt);
        glm::vec3* getPos();
        glm::vec3* getFront();
        glm::mat4* getView( void );

    private:
        glm::mat4 m_view;
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        float m_speed;
        float m_yaw = -90.0f;
        float m_pitch = 0.0f;

};


#endif