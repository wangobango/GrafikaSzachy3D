
#include "headers/king.h"

King::King(bool white,ShaderProgram *shaderProgram,GLuint tex0):Model(shaderProgram,tex0){
    if(white){
        color =1;
        texPath = "sources/white.png";
    }
    else{
        color = 0;
        texPath = "black.png";
    }

    path="models/king.obj";
    parse();
    loadArrays();
    prepare();
   
	
}

void King::draw(glm::mat4 mP,glm::mat4 mV){

    shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));
	
    if(color){
        glUniform1i(shaderProgram->getUniformLocation("textureMap0"),0); 
    	glActiveTexture(GL_TEXTURE0);

    }
    else{
	    glActiveTexture(GL_TEXTURE1);
        glUniform1i(shaderProgram->getUniformLocation("textureMap0"),1); 

    }
	glBindTexture(GL_TEXTURE_2D,tex);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES,0,vertex_count);

	glBindVertexArray(0);
}