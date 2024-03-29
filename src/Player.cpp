#include "Player.h"

bool Player::drawSpriteMode = false;

Player::Player() {
	// Set the initial position and velocity
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	movementSpeed = 1.0;
	turnSpeed = 1.0;
	rotation = 0;
	energy = 100;
	scale = 1.0;
	damping = 0.95;
	rayEmitter.setup(position, 10, ofVec2f(0, -5), 2.0f);
	canShoot = false;
	playerSprite.load(ofToDataPath("images/Player.png"));
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
	alignEmitter();
	rayEmitter.update();

	// Add this check to call shoot only when canShoot is true
	if (canShoot) {
		shoot();
		canShoot = false; // Reset the flag after shooting
	}
}

void Player::draw() {
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotate(rotation);
	ofScale(scale, scale);
	if (Player::drawSpriteMode) {
		playerSprite.draw(-playerSprite.getWidth() / 2, -playerSprite.getHeight() / 2);
	}
	else {
		ofDrawTriangle(0, -15 * scale, -10 * scale, 10 * scale, 10 * scale, 10 * scale);
	}
	ofPopMatrix();
	rayEmitter.draw();
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

void Player::increaseEnergy() {
	if (energy < 100) {
		energy += 1;
	}
}

void Player::displayEnergy() {
	ofDrawBitmapString("Energy: " + ofToString(energy), ofGetWidth() / 2, 20);
}

void Player::alignEmitter() {
	float radians = ofDegToRad(rotation -  90);
	ofVec2f direction(cos(radians), sin(radians));

	// Emitter alignment
	ofPoint tipOffset = direction * (scale);
	rayEmitter.position = position + tipOffset;

	// Emitter direction during motion
	rayEmitter.velocity = direction.normalized() * rayEmitter.velocity.length();
}

void Player::shoot() {
	if (canShoot) {
		rayEmitter.shouldEmit = true;
		canShoot = false; // Reset the flag
	}
}