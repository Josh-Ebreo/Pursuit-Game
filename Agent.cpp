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
		direction.normalize();
		velocity = direction * maxSpeed;

		// Update position
		position += velocity;

		// Update angle based on the new velocity
		angle = atan2(velocity.y, velocity.x) * RAD_TO_DEG;
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