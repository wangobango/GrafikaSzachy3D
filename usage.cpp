#include <iostream>
#include "obj_parser.h"

int main(){
    Model pion("models/szachy.obj");
    /*
    Obiekt model zawiera :
        vector< glm::vec4 > out_vertices; -> wektor wektorow wierzcholkow
        vector< glm::vec2 > out_uvs;    -> wspolrzedne tekstur
        vector< glm::vec4 > out_normals; -> ... normalsow ...
    */
}