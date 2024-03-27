#pragma once

#include "ofMain.h"

class ParticleRay {
public:
    ParticleRay();
    ParticleRay(ofPoint position, ofVec2f velocity, float lifespan);

    void update();
    void draw();
    bool isDead() const;

    ofPoint position;
    ofVec2f velocity;
    float lifespan;
    float creationTime;
};
#pragma once
