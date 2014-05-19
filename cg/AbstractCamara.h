#pragma once

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class AbstractCamara
{
public:
	AbstractCamara() ;
	virtual ~AbstractCamara(void);
	void preparaVista(float x, float y, float z, double ra, int dir);
	virtual void criaVista(double ra, float x, float y, float z) = 0;
	void setLight(int light);
	int getLight();
protected:
	void spotlight(float x, float y, float z, int dir);
	void direcional();
	GLfloat _globalAmbient[4];
	GLfloat _ambient[4];
	GLfloat _position[4];
private:
	int _light;


	
	
};

