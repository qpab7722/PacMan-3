#pragma once
#include "abstractcamara.h"
class PerspCamara :
	public AbstractCamara
{
public:
	PerspCamara();
	~PerspCamara(void);
	void criaVista(double ra, float x, float y, float z);
private:
	float _distanca;
};

