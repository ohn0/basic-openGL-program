#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
    GLuint vertexShader, fragmentShader, shaderProgram;
    int success;
    char log[512];
    public:
        Shader(const char* vShader, const char* fShader)
        {

            std::string vString;
            std::string fString;
            std::ifstream vSource(vShader, std::ifstream::in);
            std::ifstream fSource(fShader, std::ifstream::in);
            shaderProgram = glCreateProgram();

            if(vSource.fail() || fSource.fail()){
                std::cout << "Failed to load shader files." << std::endl;
            }

            while(vSource.good()){
                vString.push_back(vSource.get());
            }

            while(fSource.good()){
                fString.push_back(fSource.get());
            }
            vSource.close();
            fSource.close();

            compileShaders(vString, vertexShader, GL_VERTEX_SHADER);
            compileShaders(fString, fragmentShader, GL_FRAGMENT_SHADER);

            linkShaders(shaderProgram, vertexShader);
            linkShaders(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success){
                glGetProgramInfoLog(shaderProgram, 512, NULL, log);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED.\n" << log << std::endl;
            }
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

        }

        void use()
        {
            glUseProgram(shaderProgram);
        }

        int findUniformValue(const char* uniformValue)
        {
            int uniformLocation = glGetUniformLocation(shaderProgram, uniformValue);
            if(uniformLocation == -1){
                std::cout << "ERROR::SHADER::INVALID UNIFORM VALUE: " << uniformValue << std::endl;
                return -1;
            }
            return uniformLocation;
        }

        int setUniformValueMat4(const int& uniformLocation, const glm::mat4& matrix)
        {
            if(uniformLocation >= 0){
                glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
                return 0;
            }
            return -1;
        }

        int setUniformValueVec3(const int& uniformLocation, const glm::vec3& newVector)
        {
            if(uniformLocation >= 0){
                glUniform3fv(uniformLocation, 1, glm::value_ptr(newVector));
            }
            return -1;
        }

        int setUniformValueVec4(const int& uniformLocation, const glm::vec4& newVector)
        {
            if(uniformLocation >= 0){
                glUniform4fv(uniformLocation, 1, glm::value_ptr(newVector));
            }
            return -1;
        }

        int setUniformValueFloat(const int& uniformLocation, const GLfloat& floatValue)
        {
            if(uniformLocation >= 0){
                glUniform1f(uniformLocation, floatValue);
            }
            return 0;
        }

        int setUniformValueInt(const int& uniformLocation, const GLuint& intValue)
        {
            if(uniformLocation >= 0){
                glUniform1i(uniformLocation, intValue);
            }
            return 0;
        }

        virtual ~Shader();

    protected:

    private:
        int compileShaders(const std::string& source, GLuint& shader, GLuint shaderType)
        {
            const char* sourceCstr = source.c_str();

            shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &sourceCstr, NULL);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(shader, 512, NULL, log);
                if(shaderType == GL_VERTEX_SHADER){
                    std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED.\n" << log << std::endl;
                }
                else if(shaderType == GL_FRAGMENT_SHADER){
                    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED.\n" << log << std::endl;
                }
                else{
                    std::cout << "ERROR::SHADER::ALT_TYPE::COMPILATION FAILED.\n" << log << std::endl;
                }
                return -1;
            }
            return 0;
        }

        int linkShaders(GLuint& program, GLuint& shader)
        {
            glAttachShader(program, shader);
            return 0;
        }
};

#endif // SHADER_H
