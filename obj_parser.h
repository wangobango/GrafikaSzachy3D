#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <shader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <fstream>


using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    aiString path;
};

class Mesh{
    public:
       vector<Vertex> vertices;
       vector<unsigned int> indices;
       vector<Texture> textures;
       Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
};

class Model{
    public:
    vector<Mesh> meshes;  
    vector<Texture> textures;
    Model(string path);
    vector<Mesh> getModel(){
        return meshes;
    }
};