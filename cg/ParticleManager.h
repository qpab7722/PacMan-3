#include "Particle.h"

class ParticleManager{
private:
    Particle _particles [24];
    float _pacx, _pacy;

public:
    ParticleManager(void);
    ParticleManager(float pacx, float pacy);
    void Activate();
    void Draw();
    void Update(int dt);
    void Reset();
    bool ExplosionInCourse();
    void UpdateParticleSistemPos(float pacx, float pacy);
};
