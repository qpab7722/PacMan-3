#pragma once
#include <time.h>
#include "Labirinto.h"

class Fantasma{
private: float _posx; 
		 float _posy;
		 float _velin;
		 float _vel;
		 float _direcao; //em graus
		 float _corred;
		 float _corgreen;
		 float _corblue;
		 float _pacx;
		 float _pacy;
		 int _branco; //num de bola bonus comidas
         float _nextDir;
         bool _virou;
		
public:	Fantasma(){};
		Fantasma(float posx, float posy, float vel, float corr, float corg, float corb, float px, float py){
			_posx=posx; 
			_posy=posy;
			_velin=vel;
			_vel=vel;
			_direcao=0;
			_corred=corr;
			_corgreen=corg;
			_corblue=corb;
			_pacx=px;
			_pacy=py;
			_branco=0;
            srand(time(0));
            _direcao = 0;
            _virou = true;
		};
		void fanSet(float posx, float posy, float px, float py){
			_posx=posx; 
			_posy=posy;
			_direcao=0;
			_pacx=px;
			_pacy=py;
			_branco=0;
            _direcao = 0;
            _virou = true;
		};
		void draw(int f);
		void drawFantasma(int f);
		float dirOlhos();
        void update();
        int escolheDir (Labirinto lab,int i, int j);
        void update(Labirinto lab, int dt, float pacx, float pacy);
        int dirPac(int dirs[4], int n, bool estado);
		bool colisaoPac();
		//sets
        void setVirou(bool state) {_virou = state;};
		void setPosx(float posx){_posx=posx;};
		void setPosy(float posy){_posy=posy;};
		void setNewPosx(float deltaX);
		void setNewPosy(float deltaY);
		void setDirecao(float dir){_direcao=dir;};
		void setPacx(float posx){_pacx=posx;};
		void setPacy(float posy){_pacy=posy;};
		void setBranco(int b){_branco=b;};
        void setNewPosy(int fat, float deltat);
        void setNewPosx(int fat, float deltat);
		//gets
		float getPosx(){return _posx;};
		float getPosy(){return _posy;};
		float getVel(){return _vel;};
		float getDirecao(){return _direcao;};
		int getBranco(){return _branco;};
};

