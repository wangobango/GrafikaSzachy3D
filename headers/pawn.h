#ifndef PAWN_H
#define PAWN_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "obj_parser.h"
#include "shaderprogram.h"


class Pawn: public Model{
    public:
    Pawn(bool,ShaderProgram*,GLuint);
    void draw(glm::mat4,glm::mat4) override;
};


#endif