#include "Agent.h"

bool Agent::drawSpriteMode = false;

Agent::Agent() {
	position.set(ofGetWidth() / 2, ofGetHeight() / 2);
	velocity.set(0, 0);
	maxSpeed = 1.0;
	turningSpeed = 0.1;
	rotation = 0;
	angularVelocity = 0;
	angularAcceleration = 0;
	damping = 0.95;
	angle = 0;
	lifespan = -1;
	birthTime = ofGetElapsedTimef();
	dead = false;
	agentSprite.load(ofToDataPath("images/Agent.png"));
}

void Agent::setup(ofPoint spawnPoint, float maxSpeed, float turningSpeed) {
	position = spawnPoint;
	this->maxSpeed = maxSpeed;
	this->turningSpeed = turningSpeed;
}

void Agent::update(ofPoint playerPosition) {
	if (!isDead() && lifespan > 0 && (ofGetElapsedTimef() - birthTime > lifespan)) {
		kill();
	} else if (!isDead()) {
		updateMovement(playerPosition);
		updatePhysics();
		if (isOffScreen()) {
			dead = true;
		}
	}
}

void Agent::updateMovement(ofPoint playerPosition) {
	ofPoint direction = playerPosition - position;
	float desiredAngle = atan2(direction.y, direction.x);
	rotation = lerpAngle(rotation, ofRadToDeg(desiredAngle), turningSpeed);

	direction.normalize();

	float speedScaleFactor = 0.1;

	applyForce(direction * maxSpeed * speedScaleFactor);
}

void Agent::updatePhysics() {
	velocity += acceleration;
	velocity *= damping;
	position += velocity;

	angularVelocity += angularAcceleration;
	angularVelocity *= damping;
	rotation += angularVelocity;

	acceleration.set(0, 0);
	angularAcceleration = 0;
}

void Agent::draw() {
	ofPushMatrix();
	ofTranslate(position);
	ofRotateDeg(rotation + 90);

	if (Agent::drawSpriteMode) {
		agentSprite.draw(-agentSprite.getWidth() / 2, -agentSprite.getHeight() / 2);
	} else if (!dead) {
		ofSetColor(ofColor::red);
		ofDrawTriangle(0, -15, -10, 10, 10, 10);
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
	birthTime = ofGetElapsedTimef();
}

bool Agent::isDead() {
	return dead;
}

void Agent::kill() {
	if (!dead) {
		dead = true;
	}
}

// Function to smoothly interpolate between two angles
// Doesn't exist in my version of openFrameworks for some reason, 
// so I have to define it myself
float Agent::lerpAngle(float current, float target, float factor) {
	float delta = fmod(target - current + 360, 360);
	if (delta > 180)
		delta -= 360;
	return current + delta * factor;
}

void Agent::applyForce(ofPoint force) {
	acceleration += force;
}

void Agent::applyTorque(float torque) {
	angularAcceleration += torque;
}