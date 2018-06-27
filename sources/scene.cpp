#include "headers/scene.h"

scene::scene(ShaderProgram *sp,uint texWhite,uint texBlack,uint texChessboard){
    Model *temp;
    GLuint tex;
    bool color;
    chessboard = new Chessboard(sp,texChessboard);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            matrix[i][j]=NULL;
        }
    }
    for(int i=0;i<2;i++){
        if(i==0){
            tex= texWhite;
            color = 1;
        } 
        else if(i==1) {
            tex = texBlack;
            color = 0;
        }
        for(int j=0;j<2;j++){ // laduje gonce
            temp = new Bishop(color,sp,tex);
            allModels.push_back(temp);
            matrix[0+7*i][2+3*j]=temp;
        }
        for(int j=0;j<8;j++){ // petla ladująca pionki 
            temp= new Pawn(color,sp,tex);
            allModels.push_back(temp);
            matrix[1+5*i][j]=temp;
        }
        for(int j=0;j<2;j++){
            temp = new Knight(color,sp,tex);//laduje skoczka
            allModels.push_back(temp);
            matrix[0+7*i][1+5*j]=temp;
            
        }
        for(int j=0;j<2;j++){ // laduje wieze

            temp = new Rook(color,sp,tex);
            allModels.push_back(temp);

            matrix[7*i][7*j]=temp;
        }
       
        temp = new King(color,sp,tex);
        allModels.push_back(temp);
        matrix[7*i][4]=temp;
        temp = new Queen(color,sp,tex);
        allModels.push_back(temp);
        matrix[7*i][3]=temp; 
    }
}
scene::~scene(){
    delete chessboard;
    for(int i=0;i<allModels.size();i++){
        delete allModels[i];
    }
}
Model *scene::getChessboard(){
    return chessboard;
}

Model *scene::getFromPosition(int x,int y){
    return matrix[x][y];
}

void scene::setToPosition(int x,int y,Model *model){
    matrix[x][y]=model;
}

void scene::removeFromPosition(int x, int y){
    matrix[x][y]=NULL;
}