#pragma once

#include "ParticleExplosion.h"

ParticleExplosion::ParticleExplosion(ofPoint position, ofVec2f velocity, float lifespan)
    : position(position), velocity(velocity), lifespan(lifespan), age(0) {}

void ParticleExplosion::update() {
    position += velocity;
    age += ofGetLastFrameTime();
}

void ParticleExplosion::draw() {
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofDrawCircle(position, 2);
    ofPopStyle();
}

bool ParticleExplosion::isDead() const {
    return age >= lifespan;
}