#ifndef SCENE_H
#define SCENE_H

#include "obj_parser.h"
#include <vector>
class scene {
private:
    vector<Model> allModels;
    Model* matrix[8][8];
public: 
    Model &getFromPosition(int x,int y);

};


#endif