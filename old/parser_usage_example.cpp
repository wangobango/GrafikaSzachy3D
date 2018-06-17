#include "parser.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    Model model("models/szachy.obj");
    //vector<Mesh> meshes = model.getModel();
    //cout<<meshes[1].vertices[1].Position[1];

    return 0;

}