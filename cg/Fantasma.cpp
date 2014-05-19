#include "Fantasma.h"
#include "Olho.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat _phantomMaterials[9][4] = { { 0.0, 0.0, 0.0, 1.0 },                          //No Material
{ 1, 0.5, 0, 1.0 },                              //Diffuse Orange
{ 1.0, 0, 0, 1.0 },                              //Diffuse Red
{ 0.0, 1.0, 1.0  },                              //Diffuse Cyan
{ 0.737255, 0.560784, 0.560784, 1.0  },          //Diffuse Pink
{0.15f, 0.15f, 0.15f, 1.0 },                     //Ambient
{ 1.0, 1.0, 1.0, 1.0 },                          //Specular
{1.0, 1.0, 1.0, 1.0},                            //Diffuse White
{100, 0, 0, 0}};

void Fantasma::draw(int f){
	if(_branco > -1){
    glPushMatrix();
    glTranslated(getPosx(),getPosy(),0.0);
    glRotatef(/*dirOlhos()*/_direcao, 0.0f, 0.0f, 1.0f);
    glScalef(.8f,.8f,0.8f);
    drawFantasma(f);
	glPopMatrix();}
};

float Fantasma::dirOlhos(){ //direcao do pacman
    float p;
    if((_pacx - _posx)!=0) {
        p = atan((_pacy - _posy)/(_pacx - _posx))*(180/3.1415) + 90;
        if(_pacx<_posx) p+=180;
    }
    else {
        p = 0;
        if(_pacy>_posy) p=180;
    };
    return p;
};

GLfloat *calculateNormal(float x1,float y1, float z1, float x2,float y2, float z2){
    GLfloat normal[3];

    normal[0] = y1*z2 - z1*y2;
    normal[1] = -x1*z2 + z1*x2;
    normal[2] = x1*y2 - y1*x2;

    GLfloat norm = sqrt(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);

    for(int i=0; i<3; i++)
        normal[i] = normal[i]/norm;

    return normal;
}

//Cacula v1Xv2, sendo v1 = P2-P1 e v2 = P3 - P1
GLfloat *calculateNormalP(float *P1, float *P2, float *P3){
    GLfloat normal[3];
    float v1[3], v2[3];

    v1[0] = P2[0] - P1[0];
    v1[1] = P2[1] - P1[1];
    v1[2] = P2[2] - P1[2];

    v2[0] = P3[0] - P1[0];
    v2[1] = P3[1] - P1[1];
    v2[2] = P3[2] - P1[2];

    normal[0] = v1[1]*v2[2] - v1[2]*v2[1];
    normal[1] = -v1[0]*v2[1] + v1[2]*v2[0];
    normal[2] = v1[0]*v2[1] - v1[1]*v2[0];

    GLfloat norm = sqrt(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);

    for(int i=0; i<3; i++)
        normal[i] = normal[i]/norm;

    return normal;
}

GLfloat *rotateCoordinatesAroundZNeg60(GLfloat *vec){
    GLfloat rot[3];

    rot[0] = vec[0]/2 + sqrtf(3)/2*vec[1];
    rot[1] = -sqrtf(3)/2*vec[0]+vec[1]/2;
    rot[2] = vec[2];

    return rot;
}

GLfloat *rotateCoordinatesAroundZ60(GLfloat *vec){
    GLfloat rot[3];

    rot[0] = vec[0]/2 - sqrtf(3)/2*vec[1];
    rot[1] = sqrtf(3)/2*vec[0]+vec[1]/2;
    rot[2] = vec[2];

    return rot;
}

void Fantasma::drawFantasma(int f){
    int i=0;
    float x, y;
    x=0.225;
    y=-0.389711;
    GLfloat *normal1, *normal2, *normal3, *normal4,*normal5, *normal6, *normalaux;
    GLfloat *P1, *P2, *P3, *P4, *P5, *P6;

    P1 = (GLfloat *) malloc (3*sizeof(GLfloat));
    P2 = (GLfloat *) malloc (3*sizeof(GLfloat));
    P3 = (GLfloat *) malloc (3*sizeof(GLfloat));
    P4 = (GLfloat *) malloc (3*sizeof(GLfloat));
    P5 = (GLfloat *) malloc (3*sizeof(GLfloat));
    P6 = (GLfloat *) malloc (3*sizeof(GLfloat));

    //corpo
    if(_branco > 0){
        glMaterialfv(GL_FRONT, GL_AMBIENT, _phantomMaterials[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _phantomMaterials[7]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _phantomMaterials[6]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _phantomMaterials[8]);
    }
    else {
        glMaterialfv(GL_FRONT, GL_AMBIENT, _phantomMaterials[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _phantomMaterials[f]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _phantomMaterials[6]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _phantomMaterials[8]);
    }

    P1[0] = 0.0; P1[1] = y; P1[2] = 0.0;
    P2[0] = x; P2[1] = y; P2[2] = 0.2;
    P3[0] = -x; P3[1] = y; P2[2] = .2;
    P4[0] = x; P4[1] = y; P4[2] = 0.7;
    P5[0] = -x; P5[1] = y; P5[2] = 0.7;
    P6[0] = 0.0; P6[1] = 0.0; P6[2] = .9;

    while(i<6){
        glBegin(GL_TRIANGLE_STRIP);
        normal1 = calculateNormalP(P1, P3, P2);
        glNormal3f(normal1[0], normal1[1], normal1[2]);
        glVertex3f (P1[0], P1[1], P1[2]); //p1

        normal2 = rotateCoordinatesAroundZ60(normal1);
        for(int j = 0; j<4; j++)
            normal2[i] = (normal2[i] +normal1[i])/2;
        glNormal3f(normal2[0], normal2[1], normal2[2]);
        glVertex3f (P2[0], P2[1], P2[2]); //p2

        normal3 = rotateCoordinatesAroundZNeg60(normal1);
        for(int j = 0; j<4; j++)
            normal3[i] = (normal3[i] +normal1[i])/2;		
        glNormal3f(normal3[0], normal3[1], normal3[2]);
        glVertex3f (P3[0], P3[1], P3[2]); //p3

        normal6 = calculateNormalP(P6, P4, P5);
        normal4 = rotateCoordinatesAroundZ60(normal1);
        normalaux = rotateCoordinatesAroundZ60(normal6);
        for(int j = 0; j<4; j++)
            normal4[i] = (normal4[i] +normal1[i]+normal6[i]+normalaux[i])/4;
        glNormal3f(normal4[0], normal4[1], normal4[2]);
        glVertex3f (P4[0], P4[1], P4[2]); //p4

        normal5 = rotateCoordinatesAroundZNeg60(normal1);
        normalaux = rotateCoordinatesAroundZNeg60(normal6);
        for(int j = 0; j<4; j++)
            normal5[i] = (normal5[i] +normal1[i]+normal6[i]+normalaux[i])/4;
        glNormal3f(normal5[0], normal5[1], normal5[2]);
        glVertex3f (P5[0], P5[1], P5[2]); //p5


        glNormal3f(0, 0, 1);	
        glVertex3f (P6[0], P6[1], P6[2]); //p6
        glEnd();

        glRotatef(60,0.0f,0.0f,1.0f);
        i++;
    };
    //olhos
    Olho d;
    d.drawOlho(-0.19, y, 0.6, 45); //direito
    d.drawOlho(0.19, y, 0.6, 45); //esquerdo
    //sobrancelhas
    d.drawScelho(-0.19, y, 0.7, 15); //direito
    d.drawScelho(0.19, y, 0.7, -15); //esquerdo
};

bool emCorredor (Fantasma fan, Labirinto lab, int i, int j){
    int dir = fan.getDirecao();
    if(dir == 270){//esquerda
        if(lab.paredeQ(i,j+1) && lab.paredeQ(i,j-1) && !lab.paredeQ(i-1,j)){
            return true;
        }
    }
    else if(dir == 90){//direita
        if(lab.paredeQ(i,j+1) && lab.paredeQ(i,j-1) && !lab.paredeQ(i+1,j)){
            return true;
        }
    }
    else if(dir == 180){//cima
        if(lab.paredeQ(i-1,j) && lab.paredeQ(i+1,j) && !lab.paredeQ(i,j-1)){
            return true;
        }
    }
    else if(dir == 0 ){//baixo
        if(lab.paredeQ(i-1,j) && lab.paredeQ(i+1,j) && !lab.paredeQ(i,j+1)){
            return true;
        }
    }

    return false;
}

int Fantasma::dirPac(int dirs[4], int n, bool estado){
    float pacDir = dirOlhos();
    int nextDir = 0, oposto = 0;
    for(int i=0; i<n; i++){
        if(abs(pacDir-dirs[i]) < abs(pacDir-dirs[nextDir]))
            nextDir = i;
        else if(abs(pacDir-dirs[i]) > abs(pacDir-dirs[oposto]))
            oposto = i;
    }

    if(estado)
        nextDir = oposto;

    return nextDir;
}
int Fantasma::escolheDir (Labirinto lab,int i, int j){
    int dirPoss[4];
    int k=0, dir, aux, n=4, r;

    if(emCorredor(*this, lab, i, j)){
        return _direcao;
    }

    for(k=0, dir = _direcao; k < n; k++){
        if(dir > 270)
            dir = 0;
        dirPoss[k] = dir;
        dir = dir + 90;
    }

    for(k=0; k<n; k++){
        if(dirPoss[k] == 270){//esquerda
            if(lab.paredeQ(i-1,j)){
                if(n -1 == k){
                    n--;
                    break;
                }
                else{
                    aux = dirPoss[--n];
                    dirPoss[n] = dirPoss[k];
                    dirPoss[k] = aux;
                }
            }
        }
        else if(dirPoss[k] == 90){//direita
            if(lab.paredeQ(i+1,j)){
                if(n -1 == k){
                    n--;
                    break;
                }
                else{
                    aux = dirPoss[--n];
                    dirPoss[n] = dirPoss[k];
                    dirPoss[k] = aux;
                }
            }
        }
        else if(dirPoss[k] == 180){//cima
            if(lab.paredeQ(i,j-1)){
                if(n -1 == k){
                    n--;
                    break;
                }
                else{
                    aux = dirPoss[--n];
                    dirPoss[n] = dirPoss[k];
                    dirPoss[k] = aux;
                }
            }
        }
        else if(dirPoss[k] == 0 ){//baixo
            if(lab.paredeQ(i,j+1)){
                if(n -1 == k){
                    n--;
                    break;
                }
                else{
                    aux = dirPoss[--n];
                    dirPoss[n] = dirPoss[k];
                    dirPoss[k] = aux;
                }
            }
        }
    }

    r = rand();

    float p = ((float)r)/((float)RAND_MAX);

    if(p <= 0.75)
        r = dirPac(dirPoss, n, getBranco());
    else
        r = r%n;

    return dirPoss[r];
}

void Fantasma::setNewPosx(int fat, float deltat){
    _posx += fat * _vel * deltat;
}

void Fantasma::setNewPosy(int fat, float deltat){
    _posy += fat * _vel * deltat;
}

bool Fantasma::colisaoPac(){
	if(abs(_pacx - _posx) < 0.8f && abs(_pacy - _posy) < 0.1f) return true;
	if(abs(_pacy - _posy) < 0.8f && abs(_pacx - _posx) < 0.1f) return true;
	return false;
}

void Fantasma::update(Labirinto lab, int dt, float pacx, float pacy){
    int i, j, dir = _direcao;
    float fractpartx, fractparty, intpart, f;
    bool virou;
    float min, max;

    if(getBranco()>0)
        _vel = _velin*1/3;
    else
        _vel = _velin;

    min = 0.499;
    max = 0.501;

    fractpartx = abs( modf (_posx + 6.0f, &intpart));
    fractparty = abs( modf (_posy - 6.0f, &intpart));
    i = abs(_posx + 6.0f);
    j = abs(_posy - 6.0f);

    _pacx=pacx;
    _pacy=pacy;

    if(fractparty > min && fractparty < max && fractpartx > min && fractpartx < max)
        dir = escolheDir(lab, i, j);

    if(dir != _direcao){
        if( dir == 270 ){//esquerda
            if(!lab.paredeQ(i-1, j)){
                _direcao = 270;
            }
        }
        else if( dir == 90 ){//direita
            if(!lab.paredeQ(i+1, j)){
                _direcao = 90;
            }
        }
        else if( dir == 180 ){//cima
            if(!lab.paredeQ(i, j-1)){
                _direcao = 180;        
            }
        }
        else if(dir == 0 ){//baixo
            if(!lab.paredeQ(i, j+1)){
                _direcao = 0;
            }
        }
    }

    dir = _direcao;
    if( dir == 270 ){ //esquerda
        if(lab.paredeQ(i-1, j)){
            if(fractpartx <= 0.5){
                f=_posx;
                if(f<0)
                    setPosx(((int)f) - 0.5f);
                else
                    setPosx(((int)f) + 0.5f);
                return;
            }
        }
        setNewPosx(-1, dt);
    }
    else if( dir == 90 ){ //direita
        if(lab.paredeQ(i+1, j)){
            if(fractpartx >= 0.5){
                f=_posx;
                if(f<0)
                    setPosx(((int)f) - 0.5f);
                else
                    setPosx(((int)f) + 0.5f);
                return;
            }
        }
        setNewPosx(1, dt);
    }
    else if( dir == 180 ){ //cima
        if(lab.paredeQ(i, j-1)){
            if(fractparty <= 0.5){
                f=_posy;
                if(f<0)
                    setPosy(((int)f) - 0.5f);
                else
                    setPosy(((int)f) + 0.5f);
                return;
            }
        }
        setNewPosy(1, dt);
    }
    else if( dir == 0 ){ //baixo
        if(lab.paredeQ(i, j+1)){
            if(fractparty >= 0.5){
                f=_posy;
                if(f<0)
                    setPosy(((int)f) - 0.5f);
                else
                    setPosy(((int)f) + 0.5f);
                return;
            }
        }
        setNewPosy(-1, dt);
    }
}