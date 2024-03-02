#include "Emitter.h"

Emitter::Emitter() {
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	spawnRate = 1.0;
	agentLifeSpan = 5.0;
	agentSpeed = 2.0;
	spawning = false;
	lastSpawnTime = 0;
}

void Emitter::setup(float x, float y) {
	position = ofPoint(x, y);
}


void Emitter::update(ofPoint playerPosition) {
	if (spawning && ofGetElapsedTimef() - lastSpawnTime > spawnRate) {
		// Create a new agent
		Agent newAgent;
		newAgent.setup(position, agentSpeed);
		newAgent.setLifeSpan(agentLifeSpan);
		agents.push_back(newAgent);
		lastSpawnTime = ofGetElapsedTimef();
	}
}

void Emitter::draw() {
	for (int i = 0; i < agents.size(); i++) {
		agents[i].draw();
	}
}

void Emitter::start() {
	spawning = true;
}

void Emitter::stop() {
	spawning = false;
}

void Emitter::setSpawnRate(float spawnRate) {
	this->spawnRate = spawnRate;
}

void Emitter::setLifeSpan(float lifeSpan) {
	this->agentLifeSpan = lifeSpan;
}

void Emitter::setAgentSpeed(float speed) {
	this->agentSpeed = speed;
}