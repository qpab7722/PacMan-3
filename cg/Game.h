#pragma once
#include "Fantasma.h"
#include "Pacman.h"
#include "Labirinto.h"
#include "ParticleManager.h"
static int _showfan[3];

class Game{
private: Labirinto _lab;
		 Pacman _pac;
		 Fantasma _fan1;
		 Fantasma _fan2;
		 Fantasma _fan3;
         ParticleManager _explosion;
public: Game();
		void draw();
		void changeLabirinto(int i);
		void comeBolas(int i, int j);
		void update(int dt);
		void hud(int t);
		void hudRes(int t);
		void FanBranco();
		static void TimerMais(int value){if(_showfan[value]>-1) _showfan[value]+=1;}; //com mais
		static void TimerMenos(int value){if(_showfan[value]>0) _showfan[value]-=1;}; //com menos
		static void TimerFan(int value){_showfan[value]=0;}; //mais uma
		bool colisao(Fantasma &f, int num);
		//gets
		Pacman getPac(){return _pac;};
		//sets
		void setPacDir(float f);
};

