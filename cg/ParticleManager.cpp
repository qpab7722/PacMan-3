#include "ParticleManager.h"
//#include <stdlib.h>
//#include <math.h>
//#include <stdio.h>
#include <gl/GLUT.h>

void rotateCoordinatesAroundZ90(float vec[]){
    float rot[3];

    rot[0] = -vec[1];
    rot[1] = vec[0];
    rot[2] = vec[2];

    for(int i=0; i < 3; i++)
        vec[i] = rot[i];
}

void rotateCoordinatesAroundY30(float *vec){
    float rot[3];
    float sin30 = 1/2;
    float cos30 = sqrt(3.0)/2;

    rot[0] = cos30*vec[0]+sin30*vec[2];
    rot[1] = vec[1];
    rot[2] = -sin30*vec[0]+cos30*vec[2];

    for(int i=0; i < 3; i++)
        vec[i] = rot[i];
}

ParticleManager::ParticleManager(float pacx, float pacy){
    int i;
    float *posV;
    posV = (float *) malloc(3*sizeof(float));
    posV[0] = 1;
    posV[1] = 0;
    posV[2] = 0;
    
    _pacx = pacx;
    _pacy = pacy;

    for(i = 0; i< 13; i++)
        _particles[i] = Particle();
}


bool ParticleManager::ExplosionInCourse(){
    for(int i=0; i < 13;i++)
        if(_particles[i].getAlive())
            return true;
    return false;
}

ParticleManager::ParticleManager(void){
}

void ParticleManager::Activate(){
    for(int i = 0; i<13; i++)
        _particles[i].setAlive(true);
}

void ParticleManager::UpdateParticleSistemPos(float pacx, float pacy){
    _pacx = pacx;
    _pacy = pacy;
}

void ParticleManager::Update(int dt){
    for(int i = 0; i<13; i++){
        _particles[i].Update(dt);
    }
}

void ParticleManager::Draw(){
    glPushMatrix();
    bool isAlive;
    glTranslated(_pacx, _pacy, 0.05);
    for(int i = 0; i<13; i++){
        isAlive = _particles[i].getAlive();
        if(isAlive)
            _particles[i].Draw();
    }
    glPopMatrix();
}

void ParticleManager::Reset(){
    int i;

    for(i = 0; i < 13;i++){
            _particles[i].setPos(0,0,0);
    }
}