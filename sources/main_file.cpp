/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "headers/lodepng.h"
#include "headers/shaderprogram.h"
#include<iostream>
#include "headers/obj_parser.h"
#include "headers/bishop.h"
#include "headers/chessboard.h"
#include "headers/scene.h"
#include "ruch.cpp"
using namespace glm;

float speed_x = 0,speed_animation=0; // [radiany/s]
float speed_y = 0; // [radiany/s]
glm::vec3 actual;
float aspect=1; //Stosunek szerokości do wysokości okna

//Uchwyty na shadery
ShaderProgram *shaderProgram; //Wskaźnik na obiekt reprezentujący program cieniujący.

//Uchwyty na VAO i bufory wierzchołków
GLuint vao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
GLuint bufColors;  //Uchwyt na bufor VBO przechowujący tablicę kolorów
GLuint bufNormals; //Uchwyt na bufor VBO przechowujący tablicę wektorów normalnych
GLuint bufTexCoords; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych teksturowania

GLuint tex0;
GLuint tex1,tex2;
scene *v_scene;
bool moveFoward,moveBackward,makingMoveFoward,makingMoveBackward;
Model *beeingAnimated;
glm::vec3 animationVec;
vector<Move*> moves;

int wczytajPartie(string name){
    ifstream input(name.c_str());
    string in,color,temp;
    Coordinate start,stop;
    Move *move;
    short n=0,i=0;
    while(!input.eof()){
        input>>in;
        n=0;
        if(in!=""){
            move = new Move();
            while(in.find('-')!=string::npos){
                n++;
                i = in.find('-');
                if(n==2){
                    temp = in.substr(0,i);
                    start.x = (int)temp[0]-97;
                    start.y = (int)temp[1]-49;
                    in.erase(0,i+1);
                    move->setStartCoordinate(start);
                }
                else if(n==3){
                    temp = in.substr(0,i);
                    stop.x = (int)temp[0]-97;
                    stop.y = (int)temp[1]-49;
                    in.erase(0,i+1);
                    move->setStopCoordinate(stop);
                }
                else{
                    color = in.substr(0,i);
                    in.erase(0,i+1);
                    move->setColor(color);
                }
            }
            moves.push_back(move);
        }
   
    }
    
    
}
//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed_y = -3.14;
		if (key == GLFW_KEY_RIGHT) speed_y = 3.14;
		if (key == GLFW_KEY_UP) speed_x = -3.14;
		if (key == GLFW_KEY_DOWN) speed_x = 3.14;
		if(key == GLFW_KEY_ENTER) {moveFoward = true;
		speed_animation=0.5;}
		if(key == GLFW_KEY_BACKSPACE) moveBackward = true;
	}


	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_y = 0;
		if (key == GLFW_KEY_RIGHT) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_x = 0;
		if (key == GLFW_KEY_DOWN) speed_x = 0;
		if(key== GLFW_KEY_ENTER) {moveFoward=false;speed_animation=0;}
		if(key== GLFW_KEY_BACKSPACE) {moveBackward=false;}
	}
}

//Procedura obługi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczości
    if (height!=0) {
        aspect=(float)width/(float)height; //Stosunek szerokości do wysokości okna
    } else {
        aspect=1;
    }
}


GLuint readTexture(char* filename,int pos) {
	GLuint tex;
	switch(pos){
		case 0: {
			glActiveTexture(GL_TEXTURE0);
		}
		case 1: {
			glActiveTexture(GL_TEXTURE1);
		}
		case 2: {
			glActiveTexture(GL_TEXTURE2);
		}
	}
	

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	//Import do pamięci karty graficznej
	glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return tex;
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	
	glClearColor(0, 0, 0, 1); //Czyść ekran na czarno
	glEnable(GL_DEPTH_TEST); //Włącz używanie Z-Bufora
	glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
    glfwSetFramebufferSizeCallback(window,windowResize); //Zarejestruj procedurę obsługi zmiany rozmiaru bufora ramki


	shaderProgram=new ShaderProgram("sources/vshader.vert",NULL,"sources/fshader.glsl"); //Wczytaj program cieniujący
	tex0=readTexture("white.png",0);
	tex1=readTexture("black.png",1);
	tex2=readTexture("szachownica.png",2);

	v_scene = new scene(shaderProgram,tex0,tex1,tex2);
	wczytajPartie("partia_testowa.txt");
	moveFoward=false;
	moveBackward=false;
	makingMoveBackward=false;
	makingMoveFoward=false;
	v_scene->initiateHistory(moves.size());
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram() {
	delete shaderProgram; //Usunięcie programu cieniującego
	delete v_scene;
	glDeleteVertexArrays(1,&vao); //Usunięcie vao
	glDeleteBuffers(1,&bufVertices); //Usunięcie VBO z wierzchołkami
	glDeleteBuffers(1,&bufColors); //Usunięcie VBO z kolorami
	glDeleteBuffers(1,&bufNormals); //Usunięcie VBO z wektorami normalnymi
	glDeleteBuffers(1,&bufTexCoords); //Usunięcie VBO ze współrzednymi teksturowania
	glDeleteTextures(1,&tex0); //Usunięcie tekstury z tex0
}


//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	Model *chessboard,*model;
	chessboard = v_scene->getChessboard();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów

	glm::mat4 P = glm::perspective(90 * 3.14f / 180, aspect, 1.0f, 200.0f); //Wylicz macierz rzutowania

	glm::mat4 V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 40.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));

	
	//Wylicz macierz modelu rysowanego obiektu
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_x, glm::vec3(1, 0, 0));
	M = glm::rotate(M, angle_y, glm::vec3(0, 1, 0));

	chessboard->resetM();
	chessboard->rotate(angle_x,glm::vec3(1, 0, 0));
	chessboard->rotate(angle_y,glm::vec3(0, 1, 0));
	chessboard->draw(P,V);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			model = v_scene->getFromPosition(i,j);
			if(model!=NULL){
				model->resetM();
				
				model->applyM(M);
				if(beeingAnimated!=NULL & model==beeingAnimated){
					model->translate(actual);
				}
				else {
					model->translate(glm::vec3(21.0f-6.0f*j,2.51f,-21.0f+6.0f*i));				
				}
				if(!model->isWhite()){
					model->rotate(180*3.14f/180,glm::vec3(0.0f,1.0f,0.0f));
				}
				
				model->draw(P,V);
			}

		}
	}
	
	glfwSwapBuffers(window);

}

void animateMove(Coordinate start,Coordinate stop,int j){
	Model *model;
	glm::vec3 a,b,dif,dif2;
	bool animatex=true,animatey=true,down=false;
	model = v_scene->getFromPosition(start.y,start.x);
	a = glm::vec3(21.0f-6.0f*start.x,2.51f,-21.0f+6.0f*start.y);
	b = glm::vec3(21.0f-6.0f*stop.x,2.51f,-21.0f+6.0f*stop.y);
	float gora=12.0f;
	dif = b-a;
	dif2 = a;
	dif2.y=gora;
	dif2= dif2-a;
	if(j==0){
		actual=a;
		animatex=true;
		animatey=true;
		beeingAnimated = v_scene->getFromPosition(start.y,start.x);
	}
	else {
		glm::vec3 actualcmp(roundf(actual.x * 100) / 100,roundf(actual.y * 100) / 100,roundf(actual.z * 100) / 100);
		glm::vec3 bcmp(roundf(b.x * 100) / 100,roundf(b.y * 100) / 100,roundf(b.z * 100) / 100);
		
		if(actualcmp==bcmp){

			animatex=false;
			makingMoveBackward=false;
			makingMoveFoward=false;
			beeingAnimated=NULL;
		}
		else if(actualcmp.x==bcmp.x && actualcmp.z == bcmp.z)
		{
			animatey=true;
			down =true;
		}
		else if(actualcmp.y==roundf(gora*100)/100){
			animatey=false;
		}
		
	}
	if(animatex){
		if(animatey){
			if(down){
				dif2=dif2*(-1.0f);
				actual+=dif2*0.05f;
				down=true;
			}
			else{
				actual+=dif2*0.05f;
			}

		}
		else {
			actual+=dif*0.02f;		
		}
	
	}
	
}

int main(void)
{
	
	
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów


	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące
	

	float angle_x = 0; //Kąt obrotu obiektu
	float angle_y = 0; //Kąt obrotu obiektu

	glfwSetTime(0); //Wyzeruj licznik czasu
	Model *test;
	int i=0,j=0;
	Coordinate start,stop;
	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle_x += speed_x*glfwGetTime(); //Zwiększ kąt o prędkość kątową razy czas jaki upłynął od poprzedniej klatki
		angle_y += speed_y*glfwGetTime(); //Zwiększ kąt o prędkość kątową razy czas jaki upłynął od poprzedniej klatki
		glfwSetTime(0); //Wyzeruj licznik czasu
		if((moveFoward|| makingMoveFoward)){
			if(i<moves.size()){
				if(j==0) makingMoveFoward=true;
				if(makingMoveFoward){
					animateMove(moves[i]->getStartCoordinate(),moves[i]->getStopCoordinate(),j);
				}
				j++;
				if(!makingMoveFoward){
					start= moves[i]->getStartCoordinate();
					stop = moves[i]->getStopCoordinate();
					test=v_scene->getFromPosition(stop.y,stop.x);

					if(test!=NULL){
						v_scene->addToHistory(i,test);
					}
					test=v_scene->getFromPosition(start.y,start.x);
					v_scene->setToPosition(stop.y,stop.x,test);
					v_scene->removeFromPosition(start.y,start.x);
					i++;
					j=0;
				}
			}
		}

		if(moveBackward || makingMoveBackward){
			if(i==0 && !makingMoveBackward);
			else if(i>=0){
				if(j==0) {
					makingMoveBackward=true;
					if(i>0) i--;
				}
				if(makingMoveBackward){
					animateMove(moves[i]->getStopCoordinate(),moves[i]->getStartCoordinate(),j);
				}
				j++;
				if(!makingMoveBackward){
					stop= moves[i]->getStartCoordinate();
					start = moves[i]->getStopCoordinate();
					test=v_scene->getFromPosition(start.y,start.x);
					v_scene->setToPosition(stop.y,stop.x,test);
					v_scene->removeFromPosition(start.y,start.x);
					test = v_scene->getModelFromHitory(i);
					if(test!=NULL){
						
						v_scene->setToPosition(start.y,start.x,test);
						v_scene->addToHistory(i,NULL);
					}
					j=0;
				}

			}
		}
		drawScene(window,angle_x,angle_y); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram();

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
