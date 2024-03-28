#pragma once

#include "ofMain.h"

class ParticleExplosion {
public:
    ParticleExplosion(ofPoint position, ofVec2f velocity, float lifespan);
    void update();
    void draw();
    bool isDead() const;

    ofPoint position;
    ofVec2f velocity;
    float lifespan;
    float age;
};
