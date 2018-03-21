#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class InputHandler
{
    GLFWwindow* window;
    bool keys[1024];
    public:

        InputHandler(GLFWwindow* GLwindow)
        {
            window = GLwindow;
            for(int i = 0; i < 1024; i++){
                keys[i] = false;
            }
        }

        bool keyPressed(GLuint inputKey)
        {
            if(keys[inputKey]){
                return false;
            }
            if(glfwGetKey(window, inputKey) == GLFW_PRESS){
                keys[inputKey] = true;
                return true;
            }
            return false;
        }

        bool pressed(GLuint inputKey){
            return keys[inputKey];
        }

        void keyRelease(GLuint inputKey)
        {
            if(glfwGetKey(window, inputKey) == GLFW_RELEASE){
                keys[inputKey] = false;
            }
        }
        virtual ~InputHandler();

    protected:

    private:
};

#endif // INPUTHANDLER_H
