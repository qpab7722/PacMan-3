#pragma once
#include "Labirinto.h"
#include "Olho.h"

class Pacman{
private: float _posx; 
		 float _posy;
		 float _vel;
		 float _direcao; //em graus
		 int _nextdir; //em graus
		 int _vidas;
		 int _pontos;
		 void drawPacman();
		 double Pacman::getXSphericSurface(float a,float b, float radius);
		 double Pacman::getYSphericSurface(float a,float b, float radius);
		 double Pacman::getZSphericSurface(float a,float b, float radius);

public:	Pacman(){};
		Pacman(float posx, float posy, float vel){
			_posx=posx; 
			_posy=posy;
			_vel=vel;
			_direcao=1;
			_nextdir=-1;
			_vidas=3;
			_pontos=0;
		};
		void pacSet(float posx, float posy){
			_posx=posx; 
			_posy=posy;
			_direcao=1;
			_nextdir=-1;
			_vidas=3;
			_pontos=0;
		};
		void draw();
		int* update(float dt, Labirinto *lab);
		//sets
		void setPosx(float posx){_posx=posx;};
		void setPosy(float posy){_posy=posy;};
		void setNewPosx(int fat, float deltat);
		void setNewPosy(int fat, float deltat);
		void setDirecao(float dir){_direcao=dir; _nextdir=-1;};
		void setNextDir(int dir);
		void setPontos(int p){_pontos=p;};
		void setVidas(int v){_vidas=v;};
		//gets
		float getPosx(){return _posx;};
		float getPosy(){return _posy;};
		float getVel(){return _vel;};
		int getDirecao(){return _direcao;};
		int getNextDir(){return _nextdir;};
		int getPontos(){return _pontos;};
		int getVidas(){return _vidas;};
};
