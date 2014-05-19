#include "Pacman.h"
#include "Olho.h"
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLfloat _noM[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat _matA[] = { 0.15f, 0.15f, 0.15f, 1.0 };
GLfloat _matDYellow[] = { 1.0f, 1.0f, 0, 1.0 };
GLfloat _matS[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat _S[] = { 100.0 };


void Pacman::setNewPosx(int fat, float deltat){
	_posx += fat * _vel * deltat;
}

void Pacman::setNewPosy(int fat, float deltat){
	_posy += fat * _vel * deltat;
}

void Pacman::setNextDir(int dir){ //proxima direcao do pacman
	if(dir!=_direcao) _nextdir=dir;
}

void Pacman::draw(){
	glPushMatrix();
	glTranslated(getPosx(),getPosy(),0.25);
	glRotatef(180 + _direcao, 0.0f, 0.0f, 1.0f);
	glScalef(1.6f,1.6f,1.6f);
	drawPacman();
	glPopMatrix();
};

void Pacman::drawPacman(){
	float r=.25f;

	GLfloat position[] = {0, r, 0, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	
	//corpo
    glMaterialfv(GL_FRONT, GL_AMBIENT, _noM);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _matDYellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _matS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _S);				
	glutSolidSphere(0.25f,20,20);
	
	// Olhos
	Olho d;
	float xy_angle=45.0*3.14/180.0;
	float z_angle=-62.5*3.14/180.0;
	//olho direito
	float x = getXSphericSurface(xy_angle,z_angle,r);
	float y = getYSphericSurface(xy_angle,z_angle,r);
	float z = getZSphericSurface(xy_angle,z_angle,r);
	d.drawOlho(x, y, z, -45);
	//olho esquerdo
	x = getXSphericSurface(-xy_angle,z_angle,r);
	y = getYSphericSurface(-xy_angle,z_angle,r);
	z = getZSphericSurface(-xy_angle,z_angle,r);
	d.drawOlho(x, y, z, -45);

	//sobrecelhas
	z_angle=-75.0*3.14/180.0;
	 xy_angle=-95.0*3.14/180.0;
	d.drawScelho(getXSphericSurface(xy_angle,z_angle,r), //direito
				getYSphericSurface(xy_angle,z_angle,r),
				getZSphericSurface(xy_angle,z_angle,r),
				15);
	xy_angle=-xy_angle;
	d.drawScelho(getXSphericSurface(xy_angle,z_angle,r), //esquerdo
				getYSphericSurface(xy_angle,z_angle,r),
				getZSphericSurface(xy_angle,z_angle,r),
				-15);

	//printf("%f,%f,%f",getXSphericSurface(45.0*3.14/180.0,80*3.14/180.0,.25),
		//getYSphericSurface(45.0*3.14/180.0,80*3.14/180.0,.25),getZSphericSurface(45.0*3.14/180.0,80*3.14/180.0,.25)); //10:rad=180:PI
}

double Pacman::getYSphericSurface(float xy,float z, float radius){
	return radius * cos(z) * cos(xy);
}

double Pacman::getXSphericSurface(float xy,float z, float radius){
	return radius * cos(z) * sin(xy);
}

double Pacman::getZSphericSurface(float xy,float z, float radius){
	return radius * sin(-z);
}

//Retorna o x do pacman
int* Pacman::update(float dt, Labirinto *lab){
	int i, j, dir, res[2];
	float fractpartx, fractparty, intpart, p;

    fractpartx = abs( modf (_posx + 6.0f, &intpart));
	fractparty = abs( modf (_posy - 6.0f, &intpart));
	i = abs(_posx + 6.0f);
	j = abs(_posy - 6.0f);
	res[0]=i; res[1]=j;

	//ver direcao
	dir = _nextdir;
	if(dir!=-1){
		if( dir == 270 ){//esquerda
			if((!(*lab).paredeQ(i-1, j) && fractparty > 0.49 && fractparty < 0.51))
				_direcao = 270;
		}
		else if( dir == 90 ){//direita
			if((!(*lab).paredeQ(i+1, j) && fractparty < 0.51 && fractparty > 0.49))
				_direcao = 90;
	    }
		else if( dir == 180 ){//cima
			if((!(*lab).paredeQ(i, j-1) && fractpartx > 0.49 && fractpartx < 0.51))
				_direcao = 180;
	    }
		else if(dir == 0 ){//baixo
			if((!(*lab).paredeQ(i, j+1) && fractpartx < 0.51 && fractpartx > 0.49))
				_direcao = 0;
		}
	}
	//andar
	dir = _direcao;
	if( dir == 270 ){ //esquerda
		if((*lab).paredeQ(i-1, j)  && fractpartx <= 0.5){
			p=_posx;
			if(p<0) 
                setPosx(((int)p) - 0.5f);
			else
                setPosx(((int)p) + 0.5f);
			return res;//comeBolas(i, j, lab); //false;
        }
		setNewPosx(-1, dt);
	}
	else if( dir == 90 ){ //direita
		if((*lab).paredeQ(i+1, j)  && fractpartx >= 0.5){
			p=_posx;
			if(p<0)
                setPosx(((int)p) - 0.5f);
			else 
                setPosx(((int)p) + 0.5f);
			return res;//comeBolas(i, j, lab); //false;
        }
		setNewPosx(1, dt);
    }
	else if( dir == 180 ){ //cima
		if((*lab).paredeQ(i, j-1) && fractparty <= 0.5){
			p=_posy;
			if(p<0)
                setPosy(((int)p) - 0.5f);
			else
                setPosy(((int)p) + 0.5f);
			return res;//comeBolas(i, j, lab); //false;
        }
		setNewPosy(1, dt);
    }
	else if( dir == 0 ){ //baixo
		if((*lab).paredeQ(i, j+1)  && fractparty >= 0.5){
			p=_posy;
			if(p<0)
                setPosy(((int)p) - 0.5f);
			else
                setPosy(((int)p) + 0.5f);
			return res;//comeBolas(i, j, lab); //false;
        }
		setNewPosy(-1, dt);
	}
	return res;//comeBolas(i, j, lab);
}
