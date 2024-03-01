#pragma once

#include "ofMain.h"

class Agent {
public:
	Agent();
	void setup(ofPoint spawnPoint, float maxSpeed);
	void update(ofPoint playerPosition);
	void draw();
	bool isOffScreen();
	void setLifeSpan(float lifeSpan);
	bool isDead();

private:
	ofPoint position;
	ofPoint velocity;
	float maxSpeed;
	float angle;
	float lifespan;
	float birthTime;
	bool dead;
};