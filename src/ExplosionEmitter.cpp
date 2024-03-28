#pragma once

#include "ExplosionEmitter.h"

ExplosionEmitter::ExplosionEmitter() : numParticles(100), lifespan(1.0f) {}

void ExplosionEmitter::setup(ofPoint position, int numParticles, float lifespan) {
    ofLogNotice("ExplosionEmitter::setup") << "Position set to: " << position;
    this->position = position;
    this->numParticles = numParticles;
    this->lifespan = lifespan;

    particles.clear();
}

void ExplosionEmitter::explode() {
    for (int i = 0; i < numParticles; ++i) {
        ofVec2f velocity(ofRandom(-1, 1), ofRandom(-1, 1));
        velocity.normalize();
        velocity *= ofRandom(1, 5);  // Random speed
        particles.emplace_back(position, velocity, lifespan);
    }
}

void ExplosionEmitter::update() {
    for (auto& particle : particles) {
        particle.update();
    }
    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](const ParticleExplosion& p) { return p.isDead(); }),
        particles.end());
}

void ExplosionEmitter::draw() {
    for (auto& particle : particles) {
        particle.draw();
    }
}