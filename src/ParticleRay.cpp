#include "ParticleRay.h"

ParticleRay::ParticleRay() : position(ofPoint()), velocity(ofVec2f()), lifespan(0), creationTime(ofGetElapsedTimef()) {}

ParticleRay::ParticleRay(ofPoint position, ofVec2f velocity, float lifespan)
    : position(position), velocity(velocity), lifespan(lifespan), creationTime(ofGetElapsedTimef()) {}

void ParticleRay::update() {
    position += velocity;
    // Additional physics or behavior logic can be implemented here
}

void ParticleRay::draw() {
    // Placeholder for drawing logic, e.g., drawing a line or a simple shape
    ofDrawCircle(position, 2);  // Example: Draw a small circle at the particle's position
}

bool ParticleRay::isDead() const {
    return (ofGetElapsedTimef() - creationTime) > lifespan;
}

void ParticleRay::kill() {
    dead = true;
}