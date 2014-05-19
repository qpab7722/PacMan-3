#pragma once
#define PI 3.1415926536 /* mathematical Pi */
#define CIRC_INC (2 * PI / 30)

class Olho{
public:	Olho(void);
	    void drawOlho(double x, double y, double z, float rad);
	    void drawScelho(double x, double y, double z, double angle);
	    void circle(float x, float y, float rad);
};

