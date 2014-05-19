
#include "PerspCamara.h"


PerspCamara::PerspCamara() : AbstractCamara(){
	_distanca = 3.0f;
}


PerspCamara::~PerspCamara(void){}

void PerspCamara::criaVista(double ra, float pos_x, float pos_y, float pos_z){
	double newEyeX = pos_x ;
	double newEyeZ = _distanca;//; ( pos_z + dist);
	double newEyeY =  (pos_y-_distanca);
	gluPerspective(60.0, ra, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( newEyeX, newEyeY, newEyeZ, pos_x, pos_y, pos_z, 0, 0., 1.);
}


