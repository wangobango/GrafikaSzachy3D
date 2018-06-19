#include <iostream>
#include "../headers/obj_parser.h"

int main(){
    Model pion("../models/szachy.obj");
    /*
    Obiekt model zawiera :
        vector< glm::vec4 > out_vertices; -> wektor wektorow wierzcholkow
        vector< glm::vec2 > out_uvs;    -> wspolrzedne tekstur
        vector< glm::vec4 > out_normals; -> ... normalsow ...
  
        tak wygląda klasa :
        
        class Model{
        public:
        vector< glm::vec4 > out_vertices;
        vector< glm::vec2 > out_uvs;
        vector< glm::vec4 > out_normals;
        Model(const char* path);    
    };

   */
}