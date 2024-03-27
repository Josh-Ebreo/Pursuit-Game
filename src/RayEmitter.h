#pragma once

#include "ofMain.h"
#include "ParticleRay.h"
#include <vector>

class RayEmitter {
public:
    RayEmitter();
    void setup(ofPoint position, float emissionRate, ofVec2f velocity, float lifespan);
    void update();
    void draw();
    void emitParticle();

    std::vector<ParticleRay> particles;
    ofPoint position;
    float emissionRate;  // Particles per second
    ofVec2f velocity;
    float lifespan;
    float lastEmissionTime;
    bool shouldEmit = false;
};