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
	float randomAngle = ofRandom(TWO_PI);  // Random angle in radians
	velocity.set(cos(randomAngle) * maxSpeed, sin(randomAngle) * maxSpeed);  // Setting velocity in a random direction
	birthTime = ofGetElapsedTimef();
}

void Agent::update(ofPoint playerPosition) {
	if (!isDead() && lifespan > 0 && (ofGetElapsedTimef() - birthTime > lifespan)) {
		dead = true;
	}
	else {
		// Calculate direction towards the player
		ofPoint direction = playerPosition - position;
		float desiredAngle = atan2(direction.y, direction.x);

		// Using my custom lerpAngle function to smoothly interpolate the angle
		angle = lerpAngle(angle, desiredAngle, 0.05);

		// Use the updated angle to set the velocity
		velocity.set(cos(angle) * maxSpeed, sin(angle) * maxSpeed);

		// Update position
		position += velocity;
	}
}

void Agent::draw() {
	ofPushMatrix();
	ofTranslate(position);
	ofRotateDeg(ofRadToDeg(angle));
	ofSetColor(ofColor::red);
	ofDrawTriangle(0, -5, -10, 10, 10, 10); 
	ofSetColor(ofColor::white);
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

void Agent::kill() { 
	dead = true; 
}

// Function to smoothly interpolate between two angles
// Doesn't exist in my version of openFrameworks for some reason, 
// so I have to define it myself
float Agent::lerpAngle(float current, float target, float factor) {
	float difference = fmod(target - current + 180, 360) - 180;
	return current + difference * factor;
}