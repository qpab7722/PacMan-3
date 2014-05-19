#include "Game.h"
#include <GL/glut.h>

Game::Game(){
	 _pac = Pacman(-0.5f, -2.5f, 0.0025f); //pacman inicial
	 _lab = Labirinto(); //labirinto inicial
	_fan1 = Fantasma(0.5f, -0.5f, 0.0025f, 1.0f, 0.0f, 1.0f, -0.5f, -2.5f); //fantasma 1 inicial
	_fan2 = Fantasma(-0.5f, -0.5f, 0.0025f, 1.0f, 0.0f, 0.0f, -0.5f, -2.5f); //fantasma 2 inicial
	_fan3 = Fantasma(-0.5f, 0.5f, 0.0025f, 1.0f, 0.5f, 0.0f, -0.5f, -2.5f); //fantasma 3 inicial
	_showfan[0] = 0; _showfan[1] = 0; _showfan[2] = 0;
    _explosion = ParticleManager (_pac.getPosx(),_pac.getPosy());
}

void Game::draw(){
	_lab.draw();
    if(!_explosion.ExplosionInCourse())
	    _pac.draw();
    _explosion.Draw();
	_fan1.draw(1);
	_fan3.draw(3);
	_fan2.draw(2);
	if(_pac.getVidas()==0) hudRes(1);
	if(_lab.getNumBolas()==0) hudRes(2);
}

void Game::changeLabirinto(int i){
	_pac.pacSet(-0.5f, -2.5f);
	_fan1.fanSet(0.5f, -0.5f, -0.5, -2.5);
	_fan2.fanSet(-0.5f, -0.5f, -0.5, -2.5);
	_fan3.fanSet(-0.5f, 0.5f, -0.5, -2.5);
	_showfan[0] = 0; _showfan[1] = 0; _showfan[2] = 0;
	_lab.changeLabirinto(i);
};

void Game::setPacDir(float f){_pac.setNextDir(f);};

void Game::FanBranco(){
	_fan1.setBranco(_showfan[0]);
	_fan2.setBranco(_showfan[1]);
	_fan3.setBranco(_showfan[2]);
}

void Game::comeBolas(int i, int j){//comer bolas
	int aux=_pac.getPontos();
	if(_lab.bolaQ(i,j)){ //bola normal
		_lab.comeBola(i, j);
		_pac.setPontos(aux+3);
	}
	else if(_lab.bolaBonusQ(i,j)) { //bola bonus
		_lab.comeBola(i, j);
		_pac.setPontos(aux+3);
		TimerMais(0);
		TimerMais(1);
		TimerMais(2);
		glutTimerFunc(10000, TimerMenos, 0);
		glutTimerFunc(10000, TimerMenos, 1);
		glutTimerFunc(10000, TimerMenos, 2);
	}
}

bool Game::colisao(Fantasma &f, int num){
	if(f.colisaoPac()){
		if(f.getBranco() == 0){ //o pacman é comido
			int v = _pac.getVidas();
			if(v > 0) _pac.setVidas(v - 1);
            return true;
		}
		else { //o fantasma é comido
			_showfan[num] = -1;
			_pac.setPontos(_pac.getPontos() + 6);
			f.setPosx(-0.5f);
			f.setPosy(-0.5f);
			glutTimerFunc(5000, TimerFan, num);
            return false;
		}
	}
    return false;
}

void Game::update(int dt){
    bool explode;
	if(!(_lab.getNumBolas()==0 || _pac.getVidas() == 0)){
		int *ij;
        ij=_pac.update(dt, &_lab);
		comeBolas(ij[0], ij[1]);
		FanBranco();
		if(_showfan[0]>-1) _fan1.update(_lab, dt, _pac.getPosx(), _pac.getPosy());
		if(_showfan[1]>-1) _fan2.update(_lab, dt, _pac.getPosx(), _pac.getPosy());
		if(_showfan[2]>-1) _fan3.update(_lab, dt, _pac.getPosx(), _pac.getPosy());
		explode = colisao(_fan1, 0) || colisao(_fan2, 1) || colisao(_fan3, 2);
        if(explode){
            _explosion.Reset();
            _explosion.Activate();
            explode = false;
            _explosion.UpdateParticleSistemPos(_pac.getPosx(),_pac.getPosy());
            _pac.setPosx(-0.5f);
            _pac.setPosy(-2.5f);
            _pac.setDirecao(1);
        }
        if(_explosion.ExplosionInCourse())
            _explosion.Update(dt);
	}
};

void Game::hud(int t){ //escreve o estado do pacman
	//texto
	char text[35], aux[5];
	strcpy(text, "|PACMAN|  Vidas: ");
	itoa (_pac.getVidas(), aux, 10);
	strcat(text, aux);
	strcat(text, "  Pontos: ");
	itoa (_pac.getPontos(), aux, 10);
	strcat(text, aux);
	//escrever
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(0.35, 1.9, 0.0);
	glOrtho(0.0f, 6.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(0.0, 0.0, 0.0);
	const int length = (int)strlen(text);
	for (int i = 0; i < length; ++i)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Game::hudRes(int t){ //escreve o estado do pacman
	//texto
	char text[35], aux[5];
	if(t==1) strcpy(text, "Game Over");
	if(t==2) strcpy(text, "Weeeee!");
	//escrever
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(0.9, 0.9, 0.0);
	glOrtho(0.0f, 2.0f, 0.0f, 2.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(0.0, 0.0, 0.0);
	int length = (int)strlen(text);
	for (int i = 0; i < length; ++i)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}