#pragma once

#include "ofMain.h"
#include "Agent.h"
#include <vector>

class Emitter {
public:
	Emitter();
	void setup(float x, float y);
	void update(float elapsedTime, ofPoint playerPosition);
	void draw();
	void start();
	void stop();
	void setSpawnRate(float spawnRate);
	void setLifeSpan(float lifeSpan);
	void setAgentSpeed(float speed);
	void setAgentTurningSpeed(float turningSpeed);
	void setNAgents(int nAgents);
	void clearAgents();
	void reset(float currentTime);

	ofPoint position;
	float spawnRate;
	float agentLifeSpan;
	float agentSpeed;
	float agentTurningSpeed;
	bool spawning;
	float lastSpawnTime;

	std::vector<Agent>& getAgents() { return agents; }

	std::vector<Agent> agents;
	int nAgents;
};