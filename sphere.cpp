#include "sphere.h"
int saveSphere(char* filename,int vertexCount, float* vertices, float* normals)
{
    std::ofstream savefile;
    savefile.open(filename, std::ofstream::out | std::ofstream::trunc);
    int i = 0;
    savefile << vertexCount << " ";
    while(i < vertexCount){
        savefile << vertices[i] << " " << normals[i];
        i++;
    }
    savefile.close();

}

int loadSphere(char* filename, float* buffer, float* normals)
{
    std::ifstream savefile;
    savefile.open(filename, std::ofstream::in);
    int vertexCount;
    savefile >> vertexCount;
    char c;
    savefile >> c;
    buffer = new float[vertexCount];
    normals = new float[vertexCount];
    int i = 0;
    while(i < vertexCount){
        savefile >> buffer[i];
        savefile >> c;
        savefile >> normals[i];
//        std::cout << buffer[i] << " " << normals[i] << std::endl;
        i++;
    }
    printf("all good\n");
    return vertexCount;
}
