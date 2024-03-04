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
	void setNAgents(int nAgents);

	ofPoint position;
	float spawnRate; // The rate at which agents are spawned
	float agentLifeSpan;
	float agentSpeed;
	bool spawning;
	float lastSpawnTime;

	std::vector<Agent>& getAgents() { return agents; }

private:
	std::vector<Agent> agents;
	int nAgents;
};