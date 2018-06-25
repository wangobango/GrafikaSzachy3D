#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "shaderprogram.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "obj_parser.h"
#include <stdlib.h>
#include <stdio.h>

class Chessboard: public Model{
public:
    Chessboard(ShaderProgram* ,GLuint);
    void draw(glm::mat4,glm::mat4) override;
};

#endif