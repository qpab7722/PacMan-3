
#include "OrthoCamara.h"


OrthoCamara::OrthoCamara() : AbstractCamara(){}


OrthoCamara::~OrthoCamara(void){}

void OrthoCamara::criaVista(double ra, float x, float y, float z){
	glOrtho(-7.0f * ra, 7.0f * ra, -7.0f, 7.0f, -7.0f, 7.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
