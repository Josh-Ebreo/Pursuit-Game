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
	lifespan = -1;  // lifespan of -1 => immortal
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
	// Check if the agent has exceeded its lifespan and mark it as dead if so
	if (!isDead() && lifespan > 0 && (ofGetElapsedTimef() - birthTime > lifespan)) {
		dead = true;
	}
	else {
		// If the agent is still alive, update its movement and physics
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

	// Adjusting the agent's rotation to face the player
	rotation = lerpAngle(rotation, ofRadToDeg(desiredAngle), turningSpeed);

	// Moving towards the player
	direction.normalize();

	// Apply force in the direction of the player
	applyForce(direction * maxSpeed);
}

void Agent::updatePhysics() {
	// Apply acceleration to velocity
	velocity += acceleration;
	// Apply damping to simulate friction and prevent infinite acceleration
	velocity *= damping;
	// Update the agent's position
	position += velocity;

	// Apply angular acceleration to angular velocity
	angularVelocity += angularAcceleration;
	// Apply damping to the angular velocity to prevent infinite spinning
	angularVelocity *= damping;
	// Update the agent's rotation
	rotation += angularVelocity;

	// Reset the linear and angular acceleration for the next frame
	acceleration.set(0, 0);
	angularAcceleration = 0;
}

void Agent::draw() {
	ofPushMatrix();
	ofTranslate(position);
	ofRotateDeg(rotation + 90); // Correct the angle as previously described

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

void Agent::applyForce(ofPoint force) {
	acceleration += force;
}

void Agent::applyTorque(float torque) {
	angularAcceleration += torque;
}