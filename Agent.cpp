#include "Agent.h"

Agent::Agent() {
	// Set the initial position and velocity
	position.set(ofGetWidth() / 2, ofGetHeight() / 2);
	velocity.set(0, 0);
	maxSpeed = 1.0;
	angle = 0;
	lifespan = -1;  // lifespan of -1 => immortal
	birthTime = ofGetElapsedTimef();
	dead = false;
}

void Agent::setup(ofPoint spawnPoint, float maxSpeed) {
	position = spawnPoint;
	this->maxSpeed = maxSpeed;
}

void Agent::update(ofPoint playerPosition) {
	ofPoint direction = playerPosition - position;
	direction.normalize(); // Normalize the vector so that the agent moves at a constant speed
	velocity = direction * maxSpeed;
	position += velocity; 

	angle - atan2(direction.y, direction.x); // Calculate the angle between the direction vector and the x-axis

	if (lifespan > 0 && ofGetElapsedTimef() > birthTime + lifespan) {
		dead = true;
	}
}

void Agent::draw() {
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(ofRadToDeg(angle));
	ofDrawTriangle(0, -5, -10, 10, 10, 10);
	ofPopMatrix();
}

bool Agent::isOffScreen() {
	if (position.x < 0 || position.x > ofGetWidth() || position.y < 0 || position.y > ofGetHeight()) {
		return true;
	}
	else {
		return false;
	}
}

void Agent::setLifeSpan(float lifeSpan) {
	this->lifespan = lifeSpan;
	birthTime = ofGetElapsedTimef(); // Reset the birth time
}

bool Agent::isDead() {
	return dead;
}