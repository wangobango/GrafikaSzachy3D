#ifndef PARSER_H
#define PARSER_H
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "shaderprogram.h"
#include<iostream>

#include "headers/lodepng.h"

using namespace std;
using namespace glm;

class Model{
    protected:
    vector< glm::vec4 > out_vertices;
    vector< glm::vec2 > out_uvs;
    vector< glm::vec4 > out_normals;
    vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    int vertex_count,uvs_count,normals_count;
    float *vertices,*normals,*texCoords;
    string path,texPath;
    ShaderProgram *shaderProgram;
    glm::mat4 M;
    GLuint vao, bufVertices, bufColors, bufNormals, bufTexCoords,tex;
    bool color;
    public:
    void resetM();
    void rotate(float angle,glm::vec3 vec);
    virtual void draw(glm::mat4 mP,glm::mat4 mV)=0;
    vector< glm::vec4 > GetVertices(){
        return this->out_vertices;
    }
    void AddVertice(glm::vec4 in){
        this->out_vertices.push_back(in);
    }
    
    vector< glm::vec2 > GetUvs(){
        return this->out_uvs;
    }
    void AddUv(glm::vec2 in){
        this->out_uvs.push_back(in);
    }

    vector< glm::vec4 > GetNormals(){
        return this->out_normals;
    }
    void AddNormal(glm::vec4 in){
        this->out_normals.push_back(in);
    }

    void IncVertexCount(){
        this->vertex_count++;
    }

    int GetVertexCount(){
        return this->vertex_count;
    }

    void loadArrays();
    void parse();
    GLuint readTexture(char* );
    void prepare();
    void assignVBOtoAttribute(ShaderProgram *shaderProgram,const char* attributeName, GLuint bufVBO, int vertexSize);
    GLuint makeBuffer(void *data, int vertexCount, int vertexSize) ;
    Model(ShaderProgram*, GLuint);  
    ~Model();  
    void translate(glm::vec3);
    
};

#endif