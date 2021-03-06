#ifndef ROOK_H
#define ROOK_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "obj_parser.h"
#include "shaderprogram.h"
#include <stdlib.h>
#include <stdio.h>

class Rook: public Model{
public:
    Rook(bool,ShaderProgram* ,GLuint);
    void draw(glm::mat4,glm::mat4) override;
};

#endif