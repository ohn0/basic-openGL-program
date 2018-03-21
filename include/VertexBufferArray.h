#ifndef VERTEX_BUFFER_ARRAY_H
#define VERTEX_BUFFER_ARRAY_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "InputHandler.h"
#include "stb_image.h"
#include <iostream>

class VertexBufferArray
{
    public:
        GLuint VAO, VBO;
        GLuint type = GL_FLOAT;
        VertexBufferArray(const GLfloat* vertices, GLuint vertexSize, GLuint GL_DRAW_TYPE, GLuint newVBO = 0)
        {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            if(newVBO == 0){
                glGenBuffers(1, &VBO);
            }else{
                VBO = newVBO;
            }
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_DRAW_TYPE);
            glBindVertexArray(0);
        }

        void addVertexAttrib(GLuint location, GLuint attribSize, GLuint stride, GLuint firstPos)
        {

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glVertexAttribPointer(location, attribSize, type, GL_FALSE, stride * sizeof(float),
                                  (void*) (firstPos * sizeof(float)));
            glEnableVertexAttribArray(location);
            glBindVertexArray(0);
        }

        void addVertexAttrib(GLuint location, GLuint attribSize, GLuint stride, GLuint firstPos, const void* buffer, GLuint bufferSize)
        {
            GLuint newVBO;
            glBindVertexArray(VAO);
            glGenBuffers(1, &newVBO);
            glBindBuffer(GL_ARRAY_BUFFER, newVBO);
            glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);
            glVertexAttribPointer(location, attribSize, type, GL_FALSE, stride * sizeof(float),
                                  (void*) (firstPos * sizeof(float)));
            glEnableVertexAttribArray(location);
            glBindVertexArray(0);
        }

        void setVBO(GLuint newVBO)
        {
            VBO = newVBO;
        }

        void use()
        {
            glBindVertexArray(0);
            glBindVertexArray(VAO);
        }

        void release()
        {
            glBindVertexArray(0);
        }

        void freeBuffers()
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }

        virtual ~VertexBufferArray() { }

    protected:

    private:
};

#endif // VERTEXBUFFERARRAY_H
