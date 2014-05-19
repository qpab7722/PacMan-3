#pragma once
#include <stdlib.h>
#include <math.h>
//#include <time.h>

class Particle {
private:
    double _vel;
    float _posV[3];
    float _direcaoV[3];
    bool _alive;
    double _g;

public:
    Particle(){
        int r = rand();
        int r1=rand();
        int r2=rand();
        float f1=1, f2=1;
        _vel = 0.005;
        if(r < r1)
            f1 = -1;
        if(r < r2)
            f2 = -1;
        _direcaoV [0] = ((float)r1/(float)RAND_MAX)*_vel*f1;
        _direcaoV [1] = ((float)r2/(float)RAND_MAX)*_vel*f2;
        _direcaoV [2] = ((float)r/(float)RAND_MAX)*_vel;
        _posV[0] = 0;
        _posV[1] = 0;
        _posV[2] = 1;
        _alive = false;
        _g = 0.000005;
    };

    Particle (float posx, float posy, float posz){
        _vel = 0.003;
        float norm = sqrt(posx*posx+ posy*posy+ posz*posz);
        _direcaoV [0] = posx/((1/_vel)*norm);
        _direcaoV [1] = posy/((1/_vel)*norm);
        _direcaoV [2] = posz/((1/_vel)*norm);
        _posV[0] = posx;
        _posV[1] = posy;
        _posV[2] = posz;
        _alive = false;
        _g = 0.0000045;
    };

    void Draw ();
    void Update(int dt);
    bool getAlive();
    void setAlive(bool state);
    void setPos(float x, float y, float z);
    float * getPos();
};