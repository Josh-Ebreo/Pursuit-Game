#pragma once

#include "ofMain.h"

class Player {
public:
	Player();
	void setup(float x, float y, float speed);
	void update();
	void draw();
	void keepPlayerOnScreen();
	void rotate(float angle);

	void rotateLeft();
	void rotateRight();

	void moveUp();
	void moveDown();

	// Movement flags
	bool movingUp = false;
	bool movingDown = false;
	bool rotatingLeft = false;
	bool rotatingRight = false;

	void stopMovingUp();
	void stopMovingDown();
	void stopRotatingLeft();
	void stopRotatingRight();

	// Getters & Setters for position & speed
	ofPoint getPosition() { return position; }
	void setPosition(float x, float y) { position.set(x, y); }
	float getSpeed() { return speed; }
    void setSpeed(float speed) { this->speed = speed; }


	ofPoint position;
	float speed;
	float rotation;
	int energy;

private:
	ofImage sprite; // The sprite for the player
};