
#include "AbstractCamara.h"
#include <math.h>

float diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
float ambientSpot[] = {0.9f, 0.9f, 0.9f, 0.9f};

AbstractCamara::AbstractCamara(){

	_light = 0;
	 _globalAmbient[0] = 0.09f;
	 _globalAmbient[1] = 0.09f;
	 _globalAmbient[2] = 0.09f;
	 _globalAmbient[3] = 1.0;

	 _ambient[0] = 0.19f;
	 _ambient[1] = 0.19f;
	 _ambient[2] = 0.19f;
	 _ambient[3] = 1.0f;


	_position[0] = 1.0;
	_position[1] = -sqrt(2.0);//0.0f;
	_position[2] = 4.;//20.0f;
	_position[3] = 0.0f;

}

AbstractCamara::~AbstractCamara(void){}

void AbstractCamara::preparaVista(float x, float y, float z, double ra, int dir){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	criaVista(ra, x, y, z);

	if(_light == 1)
		spotlight(x,y,z, dir);
	else direcional();

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,_globalAmbient);

}

void AbstractCamara::spotlight(float x1, float y1, float z1, int dir){

	//90, 180, 270 dx
	//0 verso y
	//-90 sx
	float lightDir = 0.0f;
	float ylightDir = 0.0f;
	if(dir==270){
		lightDir = -90;
		ylightDir = -1.0f;
	}
	if(dir == 90){
		lightDir = 90;
		ylightDir = -1.0f;
	}
	if(dir == 180){
		lightDir = 0.0f;
		ylightDir = 1.0f;
	}
	if (dir == 0 || dir ==1){
		ylightDir = -1.0f;
		lightDir = 0.0f;
	}

	GLfloat direction[] = {lightDir, ylightDir, 0.0};
	GLdouble alpha = 2.5; //0.5
	GLdouble theta = 35; //45
	if(glIsEnabled(GL_LIGHT0)){
		glDisable(GL_LIGHT0);		
	}
	glEnable(GL_LIGHT1);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, _ambient);	//ambientSpot
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

	
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, theta); // 0~180
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, alpha); // 0~128

	//light attenuation (default values used here : no attenuation with the distance)
   /* glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);*/
}

void AbstractCamara::direcional(){
	if(glIsEnabled(GL_LIGHT1)){
		glDisable(GL_LIGHT1);		
	}
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, _ambient);	
	glLightfv(GL_LIGHT0, GL_POSITION, _position);
	
}



void AbstractCamara::setLight(int i){
	_light = i;

}

int AbstractCamara::getLight(){
	return _light;

}