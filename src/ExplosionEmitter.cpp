#pragma once

#include "ExplosionEmitter.h"

ExplosionEmitter::ExplosionEmitter() : numParticles(25), lifespan(0.5f) {}

void ExplosionEmitter::prepareEmitter(ofPoint position, int numParticles, float lifespan) {
    this->position = position;
    this->numParticles = numParticles;
    this->lifespan = lifespan;
}

void ExplosionEmitter::triggerExplosion() {
    particles.clear(); // Clear existing particles when explosion is triggered
    for (int i = 0; i < numParticles; ++i) {
        ofVec2f velocity(ofRandom(-1, 1), ofRandom(-1, 1));
        particles.emplace_back(position, velocity, lifespan);
    }
}

void ExplosionEmitter::update() {
    for (auto& particle : particles) {
        particle.update();
    }
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](const ParticleExplosion& p) {
        return p.isDead();
        }), particles.end());
}

void ExplosionEmitter::draw() {
    for (auto& particle : particles) {
        particle.draw();
    }
}