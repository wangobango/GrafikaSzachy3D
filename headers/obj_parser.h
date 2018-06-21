#ifndef PARSER_H
#define PARSER_H

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


using namespace std;


class Model{
    private:
    vector< glm::vec4 > out_vertices;
    vector< glm::vec2 > out_uvs;
    vector< glm::vec4 > out_normals;
    unsigned int vertex_count,uvs_count,normals_count;
    
    public:
    
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

    unsigned int GetVertexCount(){
        return this->vertex_count;
    }

    void loadArrays(float **vertices,float **normals, float **texCoords);
    Model(const char* path);    
};

#endif