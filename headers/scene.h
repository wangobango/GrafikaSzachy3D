#ifndef SCENE_H
#define SCENE_H

#include "obj_parser.h"
#include <vector>
#include "shaderprogram.h"
#include "bishop.h"
#include "chessboard.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
class scene {
private:
    vector<Model*> allModels;
    Model* matrix[8][8];
    Chessboard* chessboard;
    Model** history;

public: 
    Model *getFromPosition(int x,int y);
    Model *getChessboard();
    scene(ShaderProgram*,uint,uint,uint);
    ~scene();
    void setToPosition(int x,int y,Model*);
    void removeFromPosition(int x, int y);
    void initiateHistory(int size);
    Model* getModelFromHitory(int i);
    void addToHistory(int i, Model *);
};


#endif