#include "Emitter.h"
#include "Agent.h"

Emitter::Emitter() {
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	spawnRate = 1.0;
	agentLifeSpan = 5.0;
	agentSpeed = 2.0;
	spawning = false;
	lastSpawnTime = 0;
}

void Emitter::setup(float x, float y) {
	position.set(x, y);
}

void Emitter::update(float elapsedTime, ofPoint playerPosition) {
	if (spawning && elapsedTime - lastSpawnTime >= 1.0f / spawnRate) {
		for (int i = 0; i < nAgents; i++) {
			Agent newAgent;
			ofPoint spawnPoint(ofRandomWidth(), ofRandomHeight());
			newAgent.setup(spawnPoint, ofRandom(0.5 * agentSpeed, 1.5 * agentSpeed));
			newAgent.setLifeSpan(ofRandom(0.5 * agentLifeSpan, 1.5 * agentLifeSpan));
			agents.push_back(newAgent);
		}
		lastSpawnTime = elapsedTime;
	}

	for (auto& agent : agents) {
		agent.update(playerPosition);
	}

	agents.erase(std::remove_if(agents.begin(), agents.end(), [](Agent& a) { return a.isDead(); }), agents.end());
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

void Emitter::setNAgents(int n) {
	nAgents = n;
}