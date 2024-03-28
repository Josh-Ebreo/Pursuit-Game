#pragma once

#include "ofMain.h"
#include "ParticleExplosion.h"
#include <vector>

class ExplosionEmitter {
public:
    ExplosionEmitter();
    void setup(ofPoint position, int numParticles, float lifespan);
    void explode();
    void update();
    void draw();

    std::vector<ParticleExplosion> particles;
    ofPoint position;
    int numParticles;
    float lifespan;
};