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
	void kill();

	// Getters and setters for position and velocity
	ofPoint getPosition() const { return position; }
	ofPoint getVelocity() const { return velocity; }
	void setPosition(ofPoint position) { this->position = position; }
	void setVelocity(ofPoint velocity) { this->velocity = velocity; }
	void setDead(bool dead) { this->dead = dead; }

private:
	ofPoint position;
	ofPoint velocity;
	float maxSpeed;
	float angle;
	float lifespan;
	float birthTime;
	bool dead;
};