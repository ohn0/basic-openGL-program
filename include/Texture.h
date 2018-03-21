#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <SOIL.h>
#include "stb_image.h"
//#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
class Texture
{
    public:
        GLuint texture;
        Texture(const char* filename)
        {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            wrapMethod(GL_REPEAT);
            filterMethod(GL_LINEAR);
            int imgHeight, imgWidth, nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* image = stbi_load(filename, &imgWidth, &imgHeight, &nrChannels, 0);
            if(image){
                GLenum format;
                if(nrChannels == 1){
                    format = GL_RED;
                }
                else if(nrChannels == 2){
                    format = GL_RGB;
                }
                else if(nrChannels == 4){
                    format = GL_RGBA;
                }
                else{
                    std::cout << " I don't even? " << std::endl;
                    format = GL_RGB;
                }
                glGenerateMipmap(GL_TEXTURE_2D);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, image);

            }
            else{
                std::cout << "Failed to load image." << std::endl;
            }
            stbi_image_free(image);
        }
        virtual ~Texture();
        void wrapMethod(GLuint wrapping)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
        }

        void filterMethod(GLuint filtering)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
        }

        void useTexture(GLuint glTextureValue)
        {   glActiveTexture(glTextureValue);
            glBindTexture(GL_TEXTURE_2D, texture);
        }


    protected:

    private:
};

#endif // TEXTURE_H
