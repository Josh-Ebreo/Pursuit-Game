#pragma once

#include "ofMain.h"

class Player {
public:
	Player();
	void setup(float x, float y, float speed);
	void update();
	void draw();
	void move(int direction); // 0 = up, 1 = down, 2 = left, 3 = right

	ofPoint position;
	float speed;
	float rotation;
	int energy;

private:
	ofImage sprite; // The sprite for the player
};