#include "headers/scene.h"

scene::scene(ShaderProgram *sp,uint texWhite,uint texBlack,uint texChessboard){
    Model *temp;
    GLuint tex;
    bool color;
    cout<<"control scene const\n";
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
        /*for(int j=0;j<8;j++){ // petla ladująca pionki 
            temp= new Model("models/pionek.obj");
            allModels.push_back(*temp);
            matrix[1+5*i][j]=temp;
        }
        for(int j=0;j<2;j++){
            temp = new Model("models/wieza.obj");//laduje wieze
            allModels.push_back(*temp);
            martix[0+7*i][0+7*j]=temp;
        }
        for(int j=0;j<2;j++){ // laduje konie/skoczki
            temp = new Model("models/kon.obj");
            allModels.push_back(*temp);
            martix[0*7+i][1+5*j]=temp;
        }
       
        temp = new Model("models/krol.obj");
        allModels.push_back(*temp);
        martix[0*7+i][4]=temp;
        temp = new Model("models/krolowa.obj");
        allModels.push_back(*temp);
        martix[0*7+i][3]=temp; */
    }
}
scene::~scene(){
    //delete chessboard;
}
Model *scene::getChessboard(){
    return chessboard;
}

Model *scene::getFromPosition(int x,int y){
    return matrix[x][y];
}