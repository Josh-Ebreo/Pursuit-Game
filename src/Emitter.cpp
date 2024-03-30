#include "Emitter.h"
#include "Agent.h"

Emitter::Emitter() {
	position = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	spawnRate = 1.0;
	agentLifeSpan = 5.0;
	agentSpeed = 1.0;
	agentTurningSpeed = 0.25;
	spawning = false;
	lastSpawnTime = 0;
	nAgents = 0;
}

void Emitter::setup(float x, float y) {
	position.set(x, y);
}

void Emitter::update(float elapsedTime, ofPoint playerPosition) {
	if (spawning && (elapsedTime - lastSpawnTime) >= (1.0f / spawnRate)) {
		for (int i = 0; i < nAgents; i++) {
			Agent newAgent;
			ofPoint spawnPoint(ofRandomWidth(), ofRandomHeight());
			newAgent.setup(spawnPoint, agentSpeed, agentTurningSpeed);
			newAgent.setLifeSpan(agentLifeSpan);
			agents.push_back(newAgent);
		}
		lastSpawnTime = elapsedTime;
	}

	for (auto& agent : agents) {
		agent.update(playerPosition);
		std::cout << "Agent is being drawn" << std::endl;
	}

	// Remove dead agents
	agents.erase(std::remove_if(agents.begin(), agents.end(), [](Agent& a) { return a.isDead(); }), agents.end());
}

void Emitter::draw() {
	for (int i = 0; i < agents.size(); i++) {
		agents[i].draw();
	}
}

void Emitter::start() {
	spawning = true;
	lastSpawnTime = ofGetElapsedTimef();
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
	if (n >= 0) {
		nAgents = n;
	} else {
		std::cerr << "Number of agents to spawn must be non-negative." << std::endl;
	}
}

void Emitter::setAgentTurningSpeed(float turningSpeed) {
	this->agentTurningSpeed = turningSpeed;
	for (auto& agent : agents) {
		agent.setTurningSpeed(turningSpeed);
	}
}

void Emitter::clearAgents() {
	agents.clear();
}

void Emitter::reset(float currentTime) {
	clearAgents();
	lastSpawnTime = 0;
	spawning = true;
}