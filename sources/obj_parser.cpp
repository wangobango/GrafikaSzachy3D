#include "../headers/obj_parser.h"
#include <iostream>
#include <fstream>

using namespace glm;

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

Model::Model(ShaderProgram *sp,GLuint vtex){        
  M = glm::mat4(1.0f);
  tex = vtex;
  shaderProgram = sp;
}
Model::~Model(){
    delete vertices;
    delete normals;
    delete texCoords;
    //delete shaderProgram;
    glDeleteVertexArrays(1,&vao); //Usunięcie vao
	glDeleteBuffers(1,&bufVertices); //Usunięcie VBO z wierzchołkami
    glDeleteBuffers(1,&bufColors); //Usunięcie VBO z kolorami
	glDeleteBuffers(1,&bufNormals); //Usunięcie VBO z wektorami normalnymi
	glDeleteBuffers(1,&bufTexCoords); //Usunięcie VBO ze współrzednymi teksturowania
	// glDeleteTextures(1,&tex); 
}

void Model::loadArrays(){
        vertices = new float[vertex_count*4]; 
        normals = new float[vertex_count*4];
        texCoords = new float[vertex_count*2];
        for(int i=0;i<vertex_count;i++){
            vertices[i*4] = out_vertices[vertexIndices[i]-1].x;
            vertices[i*4+1] = out_vertices[vertexIndices[i]-1].y;
            vertices[i*4+2] = out_vertices[vertexIndices[i]-1].z;
            vertices[i*4+3] = out_vertices[vertexIndices[i]-1].w;
        }
         for(int i=0;i<vertex_count;i++){
            normals[i*4] = out_normals[normalIndices[i]-1].x;
            normals[i*4+1] = out_normals[normalIndices[i]-1].y;
            normals[i*4+2] = out_normals[normalIndices[i]-1].z;
            normals[i*4+3] = out_normals[normalIndices[i]-1].w;
        }
        for(int i=0;i<vertex_count;i++){
            texCoords[i*2] = out_uvs[uvIndices[i]-1].x;
            texCoords[i*2+1] = out_uvs[uvIndices[i]-1].y;
        }
}  

void Model::parse(){
           
        std::vector< glm::vec4 > temp_vertices;
        vertex_count = 0;
        uvs_count = 0;
        normals_count = 0;

        fstream file;
        file.open(path.c_str(),std::ios::in);
        string dane;
        //  if(file.good()) cout<<"udalo sie otworzyc plik"<<endl;
        //  else cout<<"nie udalo sie otworzyc pliku"<<endl;


        while (!file.eof()) 
            {
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
                    for(int i=0;i<3;i++){
                        file>>dane;
                        vector<string> temp = split(dane,'/');
                        vertexIndex[i] = stoul(temp[0]);
                        uvIndex[i] = stoul(temp[1]);
                        normalIndex[i] = stoul(temp[2]);
                        IncVertexCount();
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
    file.close();  
}
void Model::assignVBOtoAttribute(ShaderProgram *shaderProgram,const char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location=shaderProgram->getAttribLocation(attributeName); 
	glBindBuffer(GL_ARRAY_BUFFER,bufVBO);  
	glEnableVertexAttribArray(location); 
	glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 0, NULL);
}
GLuint Model::makeBuffer(void *data, int vertexCount, int vertexSize) {
    GLuint handle;

	glGenBuffers(1,&handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który będzie zawierał tablicę danych
    glBindBuffer(GL_ARRAY_BUFFER,handle);  //Uaktywnij wygenerowany uchwyt VBO
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicę do VBO

	return handle;
}
void Model::translate(glm::vec3 mM){
    M = glm::translate(M,mM);
}
void Model::prepare(){

    //Zbuduj VBO z danymi obiektu do narysowania
	bufVertices=makeBuffer(vertices, this->vertex_count, sizeof(float)*4); //VBO ze współrzędnymi wierzchołków
	
    bufNormals=makeBuffer(normals, this->vertex_count, sizeof(float)*4);//VBO z wektorami normalnymi wierzchołków
	bufTexCoords=makeBuffer(texCoords, this->vertex_count, sizeof(float)*2);//VBO ze współrzędnymi teksturowania
  
	//Zbuduj VAO wiążący atrybuty z konkretnymi VBO
	glGenVertexArrays(1,&vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(this->shaderProgram,"vertex",bufVertices,4); 
	assignVBOtoAttribute(this->shaderProgram,"normal",bufNormals,4); 
	assignVBOtoAttribute(this->shaderProgram,"texCoord0",bufTexCoords,2);  

	glBindVertexArray(0);
}
void Model::resetM(){
    M = glm::mat4(1.0f);

}
void Model::rotate(float angle,glm::vec3 vec){
    M = glm::rotate(M,angle,vec);
}

void Model::scale(glm::vec3 vec){
    M = glm::scale(M,vec);
}
void Model::setM(glm::mat4 mM){
    M = mM;
}
void Model::applyM(glm::mat4 mM){
    M = mM*M;
}
bool Model::isWhite(){
    return color;
}
