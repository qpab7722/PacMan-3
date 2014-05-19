#pragma once
#include "abstractcamara.h"
class OrthoCamara :
	public AbstractCamara
{
public:
	OrthoCamara();
	~OrthoCamara(void);
	virtual void criaVista(double ra, float x, float y, float z);
};

