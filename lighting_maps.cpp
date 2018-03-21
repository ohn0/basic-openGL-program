/////////////////////////////////////////////////////////
//DON'T FUCKING EDIT!
/////////////////////////////////////////////////////////
/*Really basic OpenGL renderer to be used to create much more complex programs.
This program creates a 3D context that successfully renders and rotates a triangle.
*/

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "InputHandler.h"
#include "stb_image.h"
#include "VertexBufferArray.h"
#include <iostream>
#include "sphere.h"


void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window,  InputHandler* inputH);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

GLfloat yaw = -90.f;
GLfloat pitch = 0.f;
double lastX = SCR_WIDTH/2;
double lastY = SCR_HEIGHT/2;
Camera camera(glm::vec3(0.f, 0.f, 3.f),
              glm::vec3(0.f, 0.f, -1.f),
              glm::vec3(0.f, 1.f, 0.f));
glm::vec3 lightPos(0.f, 0.f, 3.f);
glm::vec3 x_axis(1.f, 0.f, 0.f);
glm::vec3 y_axis(0.f, 1.f, 0.f);
glm::vec3 z_axis(0.f, 0.f, 1.f);

bool firstMouse = true;
bool keys[1024];
float deltaTime = 0.f;
float lastFrame = 0.f;
int main()
{
	//glfw: initialize and configure
	//--------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// glfw window creation
	// ---------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if(window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}



	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwMakeContextCurrent(window);
    InputHandler inputH(window);

	//tell GLFW to capture our mouse

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initalize GLEW" << std::endl;
		return -1;
	}
    glfwSetCursorPosCallback(window, mouseCallback);

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);
	//Enable alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
//	glEnable(GL_CULL_FACE);
    //Enable face culling
//    glCullFace(GL_BACK);
	//Load the shaders
    Shader mainShader("vertex.v", "fragment.fr");
    //Specify vertices

    GLfloat triangle[] = {
        -.5f, -.5f, 0.f,
         0.f,  .5f, 0.f,
         .5f, -.5f, 0.f
    };
    //Send vertices to GPU

    VertexBufferArray VBA(triangle, sizeof(triangle), GL_STATIC_DRAW);
    VBA.addVertexAttrib(0,3,3,0);

    GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int subdivideCount = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        if(inputH.keyPressed(GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, true);
        }
        if(inputH.keyPressed(GLFW_KEY_SPACE)){

        }
        if(inputH.keyPressed(GLFW_KEY_H)){
        }
        inputH.keyRelease(GLFW_KEY_SPACE);
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS){
        }
        processInput(window, &inputH);
        camera.updateCamera();
        mainShader.use();
        glm::mat4 model;
        glm::mat4 perspective = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH/(float)SCR_HEIGHT,.1f, 100.f);
        mainShader.setUniformValueMat4(mainShader.findUniformValue("projection"), perspective);


        model = glm::rotate(model, (float)(glm::radians( 1.f)*glfwGetTime()),glm::vec3(0.f,0.f,1.f));
        mainShader.setUniformValueMat4(mainShader.findUniformValue("view"), camera.viewMatrix);
        mainShader.setUniformValueMat4(mainShader.findUniformValue("model"), model);



        VBA.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float sensitivity = .05f;
    float xoffset, yoffset;
    xoffset = xpos - lastX;
    yoffset = lastY - ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;
    pitch += yoffset;
    yaw += xoffset;

    lastX = xpos;
    lastY = ypos;
    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    glm::vec3 target;
    target.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    target.y = sin(glm::radians(pitch));
    target.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    camera.cameraTarget = glm::normalize(target);
}

void processInput(GLFWwindow* window,  InputHandler* inputH)
{
    float cameraSpeed = 5 * deltaTime;
    inputH->keyPressed(GLFW_KEY_W);
    inputH->keyPressed(GLFW_KEY_A);
    inputH->keyPressed(GLFW_KEY_S);
    inputH->keyPressed(GLFW_KEY_D);

    inputH->keyRelease(GLFW_KEY_W);
    inputH->keyRelease(GLFW_KEY_A);
    inputH->keyRelease(GLFW_KEY_S);
    inputH->keyRelease(GLFW_KEY_D);

    if(inputH->pressed(GLFW_KEY_W)){
        camera.cameraPosition += cameraSpeed * camera.cameraTarget;
    }
    if(inputH->pressed(GLFW_KEY_S)){
        camera.cameraPosition -= cameraSpeed * camera.cameraTarget;
    }
    if(inputH->pressed(GLFW_KEY_A)){
        camera.cameraPosition -= glm::normalize(glm::cross(camera.cameraTarget, camera.cameraUp)) * cameraSpeed;
    }
    if(inputH->pressed(GLFW_KEY_D)){

        camera.cameraPosition += glm::normalize(glm::cross(camera.cameraTarget, camera.cameraUp)) * cameraSpeed;
    }
}
