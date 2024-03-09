#include "Player.h"

Player::Player() {
	// Set the initial position and velocity
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	speed = 5.0;
	rotation = 0;
	energy = 100;
}

void Player::setup(float x, float y, float speed) {
	position = ofPoint(x, y);
	this->speed = speed;

	//sprite.load("player.png");
}

void Player::update() {
	//Update player qualities like position, energy, etc.

	float radians = ofDegToRad(rotation - 90); // Convert degrees to radians for calculation
	ofVec2f direction(cos(radians), sin(radians)); // Calculate the direction vector based on the player's rotation

	if (movingUp) {
		position += direction * speed;
	}
	if (movingDown) {
		position -= direction * speed;
	}
	if (rotatingLeft) {
		rotate(-5.0); // Rotate left by 5 degrees
	}
	if (rotatingRight) {
		rotate(5.0); // Rotate right by 5 degrees
	}

	keepPlayerOnScreen();
}

void Player::draw() {
	if (sprite.isAllocated()) {
		sprite.draw(position.x, position.y);
	}
	else {
		ofPushMatrix();
		ofTranslate(position.x, position.y);
		ofRotate(rotation);
		ofDrawTriangle(0, -15, -10, 10, 10, 10);
		ofPopMatrix();
	}
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

void Player::rotate(float angle) {
	rotation += angle;

	if (rotation < 0) {
		rotation += 360;
	}
	else if (rotation >= 360) {
		rotation -= 360;
	}
}

void Player::rotateLeft() {
	rotatingLeft = true;
}

void Player::rotateRight() {
	rotatingRight = true;
}

void Player::moveUp() {
	movingUp = true;
}

void Player::moveDown() {
	movingDown = true;
}

void Player::stopMovingUp() {
	movingUp = false;
}

void Player::stopMovingDown() {
	movingDown = false;
}

void Player::stopRotatingLeft() {
	rotatingLeft = false;
}

void Player::stopRotatingRight() {
	rotatingRight = false;
}

void Player::decreaseEnergy() {
	energy -= 1;
}

void Player::displayEnergy() {
	ofDrawBitmapString("Energy: " + ofToString(energy), 10, 20);
}