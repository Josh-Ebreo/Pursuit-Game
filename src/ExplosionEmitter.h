#pragma once

#include "ofMain.h"
#include "ParticleExplosion.h"
#include <vector>

class ExplosionEmitter {
public:
    ExplosionEmitter();
    void prepareEmitter(ofPoint position, int numParticles, float lifespan); // New function to prepare emitter
    void triggerExplosion(); // New function to trigger explosion
    void update();
    void draw();

    std::vector<ParticleExplosion> particles;
    ofPoint position;
    int numParticles;
    float lifespan;
    bool isDone() const {
        return particles.empty();
    }
};