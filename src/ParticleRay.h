#pragma once

#include "ofMain.h"

class ParticleRay {
public:
    ParticleRay();
    ParticleRay(ofPoint position, ofVec2f velocity, float lifespan);

    void update();
    void draw();
    bool isDead() const;
    void kill();

    ofPoint position;
    ofVec2f velocity;
    float lifespan;
    float creationTime;
    bool dead;
};
#pragma once
