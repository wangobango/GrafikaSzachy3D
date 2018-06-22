#include "/headers/scene.h"

scene::scene(){
    Model *temp;
    for(int i=0;i<2;i++){
        for(int j=0;j<8;j++){ // petla ladująca pionki 
            temp= new Model("models/pionek.obj");
            allModells.push_back(*temp);
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
        for(int j=0;j<2;j++){ // laduje gonce
            temp = new Model("models/goniec.obj");
            allModels.push_back(*temp);
            martix[0*7+i][2+3*j]=temp;
        }
        temp = new Model("models/krol.obj");
        allModels.push_back(*temp);
        martix[0*7+i][4];
        temp = new Model("models/krolowa.obj");
        allModels.push_back(*temp);
        martix[0*7+i][3];
    }
}