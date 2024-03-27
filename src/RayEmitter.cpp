#include "RayEmitter.h"

RayEmitter::RayEmitter() : position(ofPoint()), emissionRate(1.0), velocity(ofVec2f()), lifespan(1.0), lastEmissionTime(0) {}

void RayEmitter::setup(ofPoint position, float emissionRate, ofVec2f velocity, float lifespan) {
    this->position = position;
    this->emissionRate = emissionRate;
    this->velocity = velocity;
    this->lifespan = lifespan;
}

void RayEmitter::update() {
    float currentTime = ofGetElapsedTimef();

    for (auto& particle : particles) {
        particle.update();
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(), [](const ParticleRay& particle) {
        return particle.isDead();
        }), particles.end());

    // The emission should only happen here, when shouldEmit is true
    if (shouldEmit) {
        emitParticle();
        shouldEmit = false; // Ensure only one particle is emitted per shoot command
        lastEmissionTime = currentTime; // Update last emission time
    }
}

void RayEmitter::draw() {
    for (auto& particle : particles) {
        particle.draw();
    }
}

void RayEmitter::emitParticle() {
    ParticleRay newParticle(position, velocity, lifespan);
    particles.push_back(newParticle);
}
