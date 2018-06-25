
#ifndef BISHOP_H
#define BISHOP_H
#include "obj_parser.h"
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Bishop:public Model{
    public:
    Bishop(bool white,ShaderProgram*,GLuint) ;
    void draw(glm::mat4 mP,glm::mat4 mV) override;
};
#endif