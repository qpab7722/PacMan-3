// cg.cpp : Defines the entry point for the console application.
//#if defined(__APPLE__) || defined(MACOSX)
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif

//#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Game.h"
#include "OrthoCamara.h"
#include "PerspCamara.h"

//Variaveis Globais
GLsizei w_global=700, h_global=550; //tamanho inicial
AbstractCamara * camara = new PerspCamara(); //camara inicial
Game jogo = Game(); //jogo inicial
int tempo_anterior=0, text=1;

void myReshape(GLsizei width, GLsizei height){
	w_global = width;
	h_global = height;
	glViewport( 0, 0, w_global, h_global);
}

void myDisplay(void) {
	float ra = ((float) w_global) / (float) h_global;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	camara->preparaVista(jogo.getPac().getPosx(), jogo.getPac().getPosy(),1.0, ra, jogo.getPac().getDirecao() );
	jogo.draw(); //desenha o jogo
	jogo.hud(text); //desenha o texto
	glFlush();
}

void handleArrowsKey(int key, int x, int y){ //teclas especiais
	if( key == GLUT_KEY_LEFT )
		jogo.setPacDir(270.0f);
	else if( key == GLUT_KEY_RIGHT )
		jogo.setPacDir(90.0f);
	else if( key == GLUT_KEY_UP )
		jogo.setPacDir(180.0f);
	else if( key == GLUT_KEY_DOWN )
		jogo.setPacDir(0.0f);
}

void handleKeys( unsigned char key, int x, int y){ //teclas normais
	if( key == 'a' ) //esquerda
		jogo.setPacDir(270.0f);
	else if( key == 'd' ) //direita
		jogo.setPacDir(90.0f);
	else if( key == 'w' ) //cima
		jogo.setPacDir(180.0f);
	else if( key == 's' ) //baixo
		jogo.setPacDir(0.0f);
	if(key=='z') //labirinto1
		jogo.changeLabirinto(1);
	else if(key=='x') //labirinto2
		jogo.changeLabirinto(2);
	else if(key=='c') //labirinto3
		jogo.changeLabirinto(3);
	else if (key == '1' ) {//camara1
		int priorValue = camara->getLight();
        camara = new PerspCamara();
		camara->setLight(priorValue);
		text=1;
	}
	else if (key == '2' ) {//camara2
		int priorValue = camara->getLight();
        camara = new OrthoCamara();
		camara->setLight(priorValue);
		text=2;
	}
	else if (key == '3')
		camara->setLight(0);
	else if (key == '4')
		camara->setLight(1);
}

void Update (){
	int tempo_actual = glutGet(GLUT_ELAPSED_TIME);
	int delta_tempo = tempo_actual - tempo_anterior; //calculo do intervalo de tempo
	tempo_anterior = tempo_actual;
	jogo.update(delta_tempo); //actualiza o jogo
	glutPostRedisplay();
}

void main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (w_global, h_global);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Pac-Man");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(handleKeys);
	glutSpecialFunc(handleArrowsKey);
    glutIdleFunc(Update);
	tempo_anterior = glutGet(GLUT_ELAPSED_TIME);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// Enable smooth shading of color
	glShadeModel(GL_SMOOTH);               
	glutMainLoop();
}
