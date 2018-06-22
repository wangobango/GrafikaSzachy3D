#include "../headers/obj_parser.h"
#include <iostream>
#include <fstream>
#include<string>

vector<string> split(const string& str, const char& ch) {
    string next;
    vector<string> result;

    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        if (*it == ch) {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        } else {
            next += *it;
        }
    }
    if (!next.empty())
         result.push_back(next);
    return result;
}

Model::Model(const char* path){        
        std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
        std::vector< glm::vec4 > temp_vertices;
        vertex_count = 0;
        uvs_count = 0;
        normals_count = 0;

        fstream file;
        file.open(path,std::ios::in);
        string dane;
        if(file.good()) cout<<"udalo sie otworzyc plik"<<endl;
        else cout<<"nie udalo sie otworzyc pliku"<<endl;


        while (!file.eof()) 
            {
                // char lineHeader[128];
                // int res = fscanf(file, "%s", lineHeader);
                // if (res == EOF)
                //     break;
                // IncVertexCount();
                // if ( strcmp( lineHeader, "v" ) == 0 ){
                //     glm::vec4 vertex;
                //     fscanf(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z );
                //     vertex.w = 1.0;
                //     IncVertexCount();
                //     temp_vertices.push_back(vertex);
                // }
                // else if ( strcmp( lineHeader, "vt" ) == 0 ){
                //     glm::vec2 uv;
                //     fscanf(file, "%f %f\n", &uv.x, &uv.y );
                //     uvs_count++;
                //     //out_uvs.push_back(uv);
                //     AddUv(uv);
                // }
                // else if ( strcmp( lineHeader, "vn" ) == 0 ){
                //     glm::vec4 normal;
                //     fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                //     normal.w = 0.0;
                //     normals_count++;
                //     //out_normals.push_back(normal);
                //     AddNormal(normal);
                // }
                // else if ( strcmp( lineHeader, "f" ) == 0 ){
                //     std::string vertex1, vertex2, vertex3;
                //     unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                //     int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                //     if (matches != 9){
                //         printf("File can't be read \n");
                //     }
                //     vertexIndices.push_back(vertexIndex[0]);
                //     vertexIndices.push_back(vertexIndex[1]);
                //     vertexIndices.push_back(vertexIndex[2]);
                //     uvIndices    .push_back(uvIndex[0]);
                //     uvIndices    .push_back(uvIndex[1]);
                //     uvIndices    .push_back(uvIndex[2]);
                //     normalIndices.push_back(normalIndex[0]);
                //     normalIndices.push_back(normalIndex[1]);
                //     normalIndices.push_back(normalIndex[2]);
                // }
                file>>dane;
                if ( dane == "v"  ){
                    glm::vec4 vertex;
                    for(int i =0; i<3;i++){
                        file>>dane;
                        switch(i){
                            case 0: vertex.x = stof(dane);
                            case 1: vertex.y = stof(dane);
                            case 2: vertex.z = stof(dane);
                        }                        
                    }
                    vertex.w = 1.0;
                    IncVertexCount();
                    //temp_vertices.push_back(vertex);
                    AddVertice(vertex);
                }
                else if (dane== "vt" ) {
                    glm::vec2 uv;
                    for(int i =0; i<2;i++){
                        file>>dane;
                        switch(i){
                            case 0: uv.x = stof(dane);
                            case 1: uv.y = stof(dane);
                        }                        
                    }
                    AddUv(uv);
                }
                else if ( dane== "vn"  ){
                    glm::vec4 normal;
                    for(int i =0; i<3;i++){
                        file>>dane;
                        switch(i){
                            case 0: normal.x = stof(dane);
                            case 1: normal.y = stof(dane);
                            case 2: normal.z = stof(dane);
                        }                        
                    }
                    normal.w = 0.0;
                    AddNormal(normal);
                }
                else if ( dane == "f" ){
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    // Wersja jesli dane oddzielone /
                    for(int i=0;i<2;i++){
                        file>>dane;
                        vector<string> temp = split(dane,'/');
                        vertexIndex[i] = stoul(temp[0]);
                        uvIndex[i] = stoul(temp[1]);
                        normalIndex[i] = stoul(temp[2]);
                    }     

                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    uvIndices    .push_back(uvIndex[0]);
                    uvIndices    .push_back(uvIndex[1]);
                    uvIndices    .push_back(uvIndex[2]);
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
                }         
    } 
    // for( unsigned int i=0; i<vertexIndices.size(); i++ ){
    //             unsigned int vertexIndex = vertexIndices[i];
    //             glm::vec4 vertex = temp_vertices[ vertexIndex-1 ];
    //             AddVertice(vertex);
    //         }
    file.close();    
}


void Model::loadArrays(float **vertices,float **normals, float **texCoords){
        float *vertices_pom,*normals_pom,*texCoords_pom;
        vertices_pom = new float[out_vertices.size()*4]; 
        normals_pom = new float[out_vertices.size()*4];
        texCoords_pom = new float[out_vertices.size()*2];
        std::cout<<out_vertices.size()<<endl;
        for(int i=0;i<out_vertices.size();i++){
            vertices_pom[i*4] = out_vertices[i].x;
            vertices_pom[i*4+1] = out_vertices[i].y;
            vertices_pom[i*4+2] = out_vertices[i].z;
            vertices_pom[i*4+3] = out_vertices[i].w;
        }
         for(int i=0;i<out_normals.size();i++){
            normals_pom[i*4] = out_normals[i].x;
            normals_pom[i*4+1] = out_normals[i].y;
            normals_pom[i*4+2] = out_normals[i].z;
            normals_pom[i*4+3] = out_normals[i].w;
        }
        for(int i=0;i<out_uvs.size();i++){
            texCoords_pom[i*2] = out_uvs[i].x;
            texCoords_pom[i*2+1] = out_uvs[i].y;
        }
        *vertices = vertices_pom;
        *normals = normals_pom;
        *texCoords = texCoords_pom;

}  
