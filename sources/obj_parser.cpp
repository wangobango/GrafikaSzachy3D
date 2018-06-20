#include "../headers/obj_parser.h"
#include<iostream>

Model::Model(const char* path){        
        std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
        std::vector< glm::vec4 > temp_vertices;
        vertex_count = 0;
        uvs_count = 0;
        normals_count = 0;

        FILE * file = fopen(path, "r");
        if( file == NULL ){
            printf("Impossible to open the file !\n");
        }
        while (1) 
            {
                char lineHeader[128];
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                    break;
                
                if ( strcmp( lineHeader, "v" ) == 0 ){
                    glm::vec4 vertex;
                    fscanf(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z );
                    vertex.w = 1.0;
                    IncVertexCount();
                    temp_vertices.push_back(vertex);
                }
                else if ( strcmp( lineHeader, "vt" ) == 0 ){
                    glm::vec2 uv;
                    fscanf(file, "%f %f\n", &uv.x, &uv.y );
                    uvs_count++;
                    //out_uvs.push_back(uv);
                    AddUv(uv);
                }
                else if ( strcmp( lineHeader, "vn" ) == 0 ){
                    glm::vec4 normal;
                    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                    normal.w = 0.0;
                    normals_count++;
                    //out_normals.push_back(normal);
                    AddNormal(normal);
                }
                else if ( strcmp( lineHeader, "f" ) == 0 ){
                    std::string vertex1, vertex2, vertex3;
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                    if (matches != 9){
                        printf("File can't be read \n");
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

                for( unsigned int i=0; i<vertexIndices.size(); i++ ){
                    unsigned int vertexIndex = vertexIndices[i];
                    glm::vec4 vertex = temp_vertices[ vertexIndex-1 ];
                    //out_vertices.push_back(vertex);
                    AddVertice(vertex);
                }

        fclose(file);
    } 
    
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
