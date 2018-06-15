#include <obj_parser.h>

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
}


Model::Model(string path){
    vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        Vertex vertex;
        
        glm::vec3 vector;
        ofstream object_file;
        object_file.open (path);
        while () )
            {
                   
            }


        object_file.close();
}