#pragma once

#include "ofMain.h"

class Agent {
public:
	Agent();
	void setup(ofPoint spawnPoint, float maxSpeed, float turningSpeed);
	void update(ofPoint playerPosition);
	void draw();
	bool isOffScreen();
	void setLifeSpan(float lifeSpan);
	bool isDead();
	void kill();
	float lerpAngle(float current, float target, float factor);
	static bool drawSpriteMode;

	ofImage agentSprite;

	ofPoint getPosition() const { return position; }
	void setTurningSpeed(float turningSpeed);

private:
	ofPoint velocity;
	ofPoint position;
	float rotation;
	float turningSpeed;
	float maxSpeed;
	float angle;
	float lifespan;
	float birthTime;
	bool dead;
};