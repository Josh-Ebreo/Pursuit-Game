#pragma once

#include "ParticleExplosion.h"

ParticleExplosion::ParticleExplosion(ofPoint position, ofVec2f velocity, float lifespan)
    : position(position), velocity(velocity), lifespan(lifespan), age(0) {}

void ParticleExplosion::update() {
    position += velocity;
    age += ofGetLastFrameTime();
}

void ParticleExplosion::draw() {
    ofDrawCircle(position, 2);  // Simple representation
}

bool ParticleExplosion::isDead() const {
    return age >= lifespan;
}