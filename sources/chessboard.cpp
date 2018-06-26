#include "headers/chessboard.h"

Chessboard::Chessboard(ShaderProgram *sp,GLuint vtex):Model(sp,vtex){
	path="models/szachownica.obj";
    parse();
    loadArrays();
    prepare();
}

void Chessboard::draw(glm::mat4 mP,glm::mat4 mV){
    shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));

    glUniform1i(shaderProgram->getUniformLocation("textureMap0"),2); 
    glActiveTexture(GL_TEXTURE2);
	
    glBindTexture(GL_TEXTURE_2D,tex);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES,0,vertex_count);

	glBindVertexArray(0);
}