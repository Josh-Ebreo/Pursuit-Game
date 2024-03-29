#pragma once

#include "ofMain.h"
#include "RayEmitter.h"

class Player {
public:
	Player();
	void setup(float x, float y, float movementSpeed, float turnSpeed);
	void update();
	void draw();
	void keepPlayerOnScreen();
	ofImage playerSprite;
	static bool drawSpriteMode;

	// Movement flags
	bool movingUp = false;
	bool movingDown = false;
	bool rotatingLeft = false;
	bool rotatingRight = false;
	bool energyHasBeenSet = false;

	void applyForce(ofPoint force);
	void applyTorque(float torque);
	void decreaseEnergy();
	void increaseEnergy();
	void displayEnergy();

	ofPoint getPosition() { return position; }
	void setPosition(float x, float y) { position.set(x, y); }
	float getMovementSpeed() { return movementSpeed; }
	void setMovementSpeed(float movementSpeed) { this->movementSpeed = movementSpeed; }
	float getTurnSpeed() { return turnSpeed; }
	void setTurnSpeed(float turnSpeed) { this->turnSpeed = turnSpeed; }
	float getScale() { return scale; }
	void setScale(float scale) { this->scale = scale; }

	ofPoint position;
	ofVec2f velocity;
	ofVec2f acceleration;
	float scale;
	float damping;
	int energy;

	float movementSpeed;
	float turnSpeed;

	float angularVelocity;
	float angularAcceleration;
	float rotation;

	ofImage sprite; // The sprite for the player

	void updateMovement();
	void updatePhysics();

	RayEmitter rayEmitter; // The particle emitter for the player
	void alignEmitter();
	void shoot();
	bool canShoot = false;
};