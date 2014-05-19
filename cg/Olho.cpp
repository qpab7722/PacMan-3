
#include "Olho.h"
#include <math.h>
#include <GL/glut.h>

Olho::Olho(void){}
GLfloat _noMate[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat _matAmb[] = { 0.15f, 0.15f, 0.15f, 1.0 };
GLfloat _matDBlack[] = { 0, 0, 0, 1.0 };
GLfloat _matDWhite[] = { 1.0f, 1.0f, 1.0f, 1.0 };
GLfloat _matSpec[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat _Sh[] = { 50.0 };

void Olho::drawOlho(double x, double y, double z, float rad){ //centrado em (x, y, z)
    glMaterialfv(GL_FRONT, GL_AMBIENT, _noMate);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _matDWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _Sh);

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rad,1,0,0);
    glutSolidSphere(0.05f,10,10);
	circle(0, 0.05f, 0.015f);
	glPopMatrix();
}

void Olho::drawScelho(double x, double y, double z, double angle){ //centrado em (x, y, z) e com inclinacao angle
    glMaterialfv(GL_FRONT, GL_AMBIENT, _noMate);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _matDBlack);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _Sh);
	glPushMatrix();	
	glTranslatef(x, y, z);
	glRotatef(90,0,0,1);
	glRotatef(angle,1,0,0);
	glScalef(0.2, 0.6, 0.1);    
	glutSolidSphere(0.1f,10,10);
	glPopMatrix();
}

void Olho::circle(float x, float y, float rad){ 
    glMaterialfv(GL_FRONT, GL_AMBIENT, _noMate);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _matDBlack);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _Sh);
	glPushMatrix();	
	glTranslatef(x, 0, y);
	glutSolidSphere(rad,10,10);
	glPopMatrix();
}