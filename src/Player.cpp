#include "Player.h"

Player::Player() {
	// Set the initial position and velocity
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	movementSpeed = 1.0;
	turnSpeed = 1.0;
	rotation = 0;
	energy = 100;
	scale = 1.0;
	damping = 0.95;
}

void Player::setup(float x, float y, float movementSpeed, float turnSpeed) {
	position.set(x, y);
	this->movementSpeed = movementSpeed;
	this->turnSpeed = turnSpeed;

	//sprite.load("player.png");
}

void Player::update() {
	updateMovement();
	updatePhysics();
	keepPlayerOnScreen();
	displayEnergy();
}

void Player::draw() {
	if (sprite.isAllocated()) {
		sprite.draw(position.x, position.y);
	}
	else {
		ofPushMatrix();
		ofTranslate(position.x, position.y);
		ofRotate(rotation);
		ofScale(scale, scale);
		ofDrawTriangle(0, -15 * scale, -10 * scale, 10 * scale, 10 * scale, 10 * scale);
		ofPopMatrix();
	}
}

void Player::updateMovement() {
	// Convert degrees to radians for calculation
	float radians = ofDegToRad(rotation - 90);

	// Calculate the direction vector based on the player's rotation
	ofVec2f direction(cos(radians), sin(radians));
	
	float slowDownMovement = 0.25;
	float slowDownTurn = 0.05;

	float slowMovementSpeed = movementSpeed * slowDownMovement;
	float slowTurnSpeed = turnSpeed * slowDownTurn;

	// Use movementSpeed for force calculation
	if (movingUp) acceleration += direction * slowMovementSpeed;
	if (movingDown) acceleration -= direction * slowMovementSpeed;

	// Use turnSpeed for angular acceleration
	if (rotatingLeft) angularAcceleration -= slowTurnSpeed;
	if (rotatingRight) angularAcceleration += slowTurnSpeed;
}

void Player::updatePhysics() {
	// Update velocity based on acceleration
	velocity += acceleration;
	velocity *= damping;
	position += velocity;

	// Update angular velocity and rotation
	angularVelocity += angularAcceleration;
	angularVelocity *= damping;
	rotation += angularVelocity;

	// Reset acceleration
	acceleration.set(0, 0);
	angularAcceleration = 0;

	// Update angular velocity and rotation
	angularVelocity += angularAcceleration;
	rotation += angularVelocity;
}

void Player::applyForce(ofPoint force) {
	acceleration += force / movementSpeed;
}

void Player::applyTorque(float torque) {
	angularAcceleration += torque / turnSpeed;
}

void Player::keepPlayerOnScreen() {
	if (position.x < 0) {
		position.x = 0;
	}
	else if (position.x > ofGetWidth()) {
		position.x = ofGetWidth();
	}
	if (position.y < 0) {
		position.y = 0;
	}
	else if (position.y > ofGetHeight()) {
		position.y = ofGetHeight();
	}
}

void Player::decreaseEnergy() {
	energy -= 1;
}

void Player::displayEnergy() {
	ofDrawBitmapString("Energy: " + ofToString(energy), ofGetWidth() / 2, 20);
}