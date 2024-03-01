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

void Player::move(int direction) {
	switch (direction) {
	case 0: // Up
		position.y -= speed;
		rotation = 0;
		break;
	case 1: // Down
		position.y += speed;
		rotation = 90;
		break;
	case 2: // Left
		position.x -= speed;
		rotation = 180;
		break;
	case 3: // Right
		position.x += speed;
		rotation = 270;
		break;
	}

	// Keep the player on the screen
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