#include "Agent.h"

bool Agent::drawSpriteMode = false;

Agent::Agent() {
	position.set(ofGetWidth() / 2, ofGetHeight() / 2);
	velocity.set(0, 0);
	maxSpeed = 1.0;
	angle = 0;
	lifespan = -1;  // lifespan of -1 => immortal
	birthTime = ofGetElapsedTimef();
	dead = false;
	agentSprite.load(ofToDataPath("images/Agent.png"));
}

void Agent::setup(ofPoint spawnPoint, float maxSpeed, float turningSpeed) {
	position = spawnPoint;
	this->maxSpeed = maxSpeed;
	this->turningSpeed = turningSpeed;
	float randomAngle = ofRandom(TWO_PI);  
	velocity.set(cos(randomAngle) * maxSpeed, sin(randomAngle) * maxSpeed); 
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
		angle = lerpAngle(angle, desiredAngle, turningSpeed);
		// Use the updated angle to set the velocity
		velocity.set(cos(angle) * maxSpeed, sin(angle) * maxSpeed);
		// Update position
		position += velocity;
	}
}

void Agent::draw() {
	ofPushMatrix();
	ofTranslate(position);
	ofRotateDeg(ofRadToDeg(angle) - 270); // Correct the angle as previously described

	if (Agent::drawSpriteMode) {
		agentSprite.draw(-agentSprite.getWidth() / 2, -agentSprite.getHeight() / 2);
	}
	else {
		// Draw the triangle representation
		ofSetColor(ofColor::red);
		ofDrawTriangle(0, -15, -10, 10, 10, 10); // Make sure these coordinates are correct
		ofSetColor(ofColor::white);
	}

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

void Agent::setTurningSpeed(float turningSpeed) {
	this->turningSpeed = turningSpeed;
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
	float delta = target - current;
	float difference = fmod(delta + PI, TWO_PI) - PI;
	return current + difference * factor * turningSpeed;
}