#include "Particle.h"
//#include <math.h>
//#include <cstdio>
#include <GL/GLUT.h>

void Particle::Draw(){
    GLfloat _noM[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat _matA[] = { 0.15f, 0.15f, 0.15f, 1.0 };
    GLfloat _matDYellow[] = { 1.0f, 1.0f, 0, 1.0 };
    GLfloat _matS[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat _S[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, _matA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _matDYellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _matS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _S);				
    glPushMatrix();
    glTranslated(_posV[0],_posV[1], _posV[2]);
    glScalef(1.6f,1.6f,1.6f);
    glutSolidSphere(.05,20,20);
    glPopMatrix();
}


void Particle::Update(int dt){
    int r;
    if(_alive){
        int i;
        for(i = 0; i < 3; i++){
            _posV[i] += _direcaoV[i]*dt;
        }
        _direcaoV[2] -= _g*dt;
        if(_posV[2] <= 0){
            _alive = false;
            r = rand();
            _direcaoV [2] = ((float)r/(float)RAND_MAX)*_vel;
        }
    }
}
bool Particle::getAlive(){
    return _alive;
}

void Particle::setAlive(bool state){
    _alive = state;
}

void Particle::setPos(float x, float y, float z){
    _posV[0] = x;
    _posV[1] = y;
    _posV[2] = z;
}

float * Particle::getPos(){
    return _posV;
}