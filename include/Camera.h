#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <iostream>

class Camera
{

    public:
        glm::mat4 viewMatrix;
        glm::vec3 cameraUp;
        glm::vec3 cameraPosition;
        glm::vec3 cameraTarget;
        Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
        {
            cameraUp = up;
            cameraPosition = position;
            cameraTarget = target;
            updateCamera();
        }

        int updateCamera()
        {
            viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraTarget, cameraUp);
            return 0;
        }


        virtual ~Camera() { }

    protected:

    private:
};

#endif // CAMERA_H
