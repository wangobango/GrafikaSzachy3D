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
    public:
    vector< glm::vec4 > GetVertices(){
        return Model::out_vertices;
    }
    unsigned int vertex_count,uvs_count,normals_count;
    void loadArrays(float **vertices,float **normals, float **texCoords);
    Model(const char* path);    
};