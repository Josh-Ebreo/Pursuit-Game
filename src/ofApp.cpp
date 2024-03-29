#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	SpaceBackground.load(ofToDataPath("images/SpaceBackground.png"));
	player.setup(ofGetWidth() / 2, ofGetHeight() / 2, 1, 1);
	setupKeyMap();
	initializeGui();

	// Set up the emitter
	agentEmitter.setup(ofGetWidth() / 2, ofGetHeight() / 2);
	agentEmitter.setSpawnRate(1.0);
	agentEmitter.setAgentSpeed(0.75);
	agentEmitter.setAgentTurningSpeed(1);
	agentEmitter.setLifeSpan(5.0);
	agentEmitter.setNAgents(5);
	agentEmitter.start(); // This starts the spawning processly

	// Game state initialization
	gameTime = ofGetElapsedTimef();
	finalGameTime = 0;
	gameStarted = false;
	isGameOver = false;
	bDifficultyChanged = false;
	difficultyHasBeenSet = false;
}

void ofApp::initializeGui() {
	gui.setup();

	// Set up the GUI parameters
	playerScaleParam.set("Player Scale", 1.0, 0.5, 2.0);
	playerMovementSpeedParam.set("Player Movement Speed", 1.0, 0.5, 2.0);
	playerTurningSpeedParam.set("Player Turning Speed", 1.0, 1.0, 2.0);
	spawnRateParam.set("Agent Spawn Rate", 3.0, 0.5, 5.0);
	agentSpeedParam.set("Agent Speed", 1.0, 0.75, 2.0);
	agentTurningSpeedParam.set("Agent Turning Speed", 1.0, 0.5, 1.5);
	agentLifeSpanParam.set("Agent Life Span", 5.0, 1.0, 15.0);
	nAgentsParam.set("Number of Agents", 5, 1, 5);

	// Add parameters to the GUI
	gui.add(difficultyLevel.setup("Difficulty Level", 1, 1, 3));
	gui.add(playerScaleParam);
	gui.add(playerMovementSpeedParam);
	gui.add(playerTurningSpeedParam);
	gui.add(spawnRateParam);
	gui.add(agentSpeedParam);
	gui.add(agentTurningSpeedParam);
	gui.add(agentLifeSpanParam);
	gui.add(nAgentsParam);
	gui.add(showGui.setup("Show GUI", true));

	// Add listeners to the parameters
	difficultyLevel.addListener(this, &ofApp::difficultyChanged);
	playerScaleParam.addListener(this, &ofApp::onPlayerScaleChanged);
	playerMovementSpeedParam.addListener(this, &ofApp::onPlayerMovementSpeedChanged);
	playerTurningSpeedParam.addListener(this, &ofApp::onPlayerTurningSpeedChanged);
	spawnRateParam.addListener(this, &ofApp::onSpawnRateChanged);
	agentSpeedParam.addListener(this, &ofApp::onAgentSpeedChanged);
	agentTurningSpeedParam.addListener(this, &ofApp::onAgentTurningSpeedChanged);
	agentLifeSpanParam.addListener(this, &ofApp::onAgentLifeSpanChanged);
	nAgentsParam.addListener(this, &ofApp::onNAgentsChanged);
}

//--------------------------------------------------------------

void ofApp::update() {
	float currentElapsedTime = ofGetElapsedTimef();
	if (gameStarted && !isGameOver) {
		updateGameState(currentElapsedTime);
	}
}

void ofApp::draw() {
	SpaceBackground.draw(0, 0);
	
	// Display "Press the Space Bar to start" at the beginning of the game
	if (!gameStarted) {
		string startMessage = "Press the Space Bar to start";
		ofDrawBitmapString(startMessage, ofGetWidth() / 2 - startMessage.length() * 4, ofGetHeight() / 2); // Adjust positioning as needed
	}

	if (!isGameOver && gameStarted) {
		drawGame();
	}
	else if (isGameOver) {
		drawGameOver();
	}

	// Display frame rate
	ofDrawBitmapString("Frame Rate: " + ofToString(ofGetFrameRate(), 2), ofGetWidth() - 180, 20);
}

void ofApp::drawGame() {
	player.draw();
	agentEmitter.draw();
	for (auto& explosion : explosions) {
		explosion.draw();
	}

	if (showGui) {
		gui.draw();
	}

	// Display ongoing game time
	float currentGameTime = ofGetElapsedTimef() - gameTime;
	ofDrawBitmapString("Game Time: " + ofToString(currentGameTime, 2) + " seconds", ofGetWidth() - 210, 40);

	// Display the player's energy in the upper center of the screen
	string energyText = "Energy: " + ofToString(player.energy);
	ofDrawBitmapString(energyText, (ofGetWidth() - energyText.length() * 8) / 2, 20); // 8 is approx width of a character
}

void ofApp::drawGameOver() {
	ofDrawBitmapString("Game Over! Press R to restart", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
	ofDrawBitmapString("Final Game Time: " + ofToString(finalGameTime, 2) + " seconds", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 20);
}

void ofApp::updateGameState(float currentElapsedTime) {
	player.update();
	agentEmitter.update(currentElapsedTime - gameTime, player.getPosition());

	for (auto& explosion : explosions) {
		explosion.update();
	}
	// Remove dead explosions
	explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
		[](const ExplosionEmitter& e) { return e.isDone(); }),
		explosions.end());

	checkPlayerAgentCollisions();
	checkParticleAgentCollisions();

	// Handle game over condition
	if (player.energy <= 0) {
		isGameOver = true;
		finalGameTime = currentElapsedTime - gameTime;
	}
}

void ofApp::checkPlayerAgentCollisions() {
	for (auto& agent : agentEmitter.getAgents()) {
		// Collision detection logic
		bool agentCollisionDetected = player.getPosition().distance(agent.getPosition()) < collisionDistance;
		if (agentCollisionDetected && !agent.isDead()) {
			ExplosionEmitter explosion;
			explosion.prepareEmitter(agent.getPosition(), 10, 0.5);
			explosion.triggerExplosion();
			explosions.push_back(explosion);
			agent.kill();
			player.decreaseEnergy();
		}
	}
}

void ofApp::checkParticleAgentCollisions() {
	for (auto& particle : player.rayEmitter.particles) {
		for (auto& agent : agentEmitter.getAgents()) {
			// Check for collision between particle and agent
			bool agentCollisionDetected = particle.position.distance(agent.getPosition()) < collisionDistance;
			if (agentCollisionDetected && !agent.isDead()) {
				ExplosionEmitter explosion;
				explosion.prepareEmitter(agent.getPosition(), 10, 0.5);
				explosion.triggerExplosion();
				explosions.push_back(explosion);
				agent.kill();
				player.increaseEnergy();
			}
		}
	}
}

void ofApp::setupKeyMap() {
	keyMap['w'] = MOVE_UP;
	keyMap['W'] = MOVE_UP;
	keyMap['s'] = MOVE_DOWN;
	keyMap['S'] = MOVE_DOWN;
	keyMap['a'] = ROTATE_LEFT;
	keyMap['A'] = ROTATE_LEFT;
	keyMap['d'] = ROTATE_RIGHT;
	keyMap['D'] = ROTATE_RIGHT;
	keyMap['g'] = TOGGLE_GUI;
	keyMap['G'] = TOGGLE_GUI;
	keyMap[' '] = START_GAME;
	keyMap['r'] = RESTART_GAME; 
	keyMap['R'] = RESTART_GAME;
	keyMap['t'] = TOGGLE_AGENT;
	keyMap['T'] = TOGGLE_AGENT;
	keyMap['k'] = SHOOT;
	keyMap['K'] = SHOOT;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (keyMap.find(key) != keyMap.end()) {
		PlayerAction action = keyMap[key];
		switch (action) {
		case START_GAME:
			if (!gameStarted) {
				gameStarted = true;
				gameTime = ofGetElapsedTimef();
				agentEmitter.start();
			}
			break;
		case RESTART_GAME:
			if (isGameOver) {
				restartGame();
			}
			break;
		case MOVE_UP:
			player.movingUp = true;
			break;
		case MOVE_DOWN:
			player.movingDown = true;
			break;
		case ROTATE_LEFT:
			player.rotatingLeft = true;
			break;
		case ROTATE_RIGHT:
			player.rotatingRight = true;
			break;
		case TOGGLE_GUI:
			showGui = !showGui;
			break;
		case TOGGLE_AGENT:
			toggleAgentSprite();
			break;
		case SHOOT:
			player.canShoot = true;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (keyMap.find(key) != keyMap.end()) {
		PlayerAction action = keyMap[key];

		switch (action) {
		case MOVE_UP:
			player.movingUp = false;
			break;
		case MOVE_DOWN:
			player.movingDown = false;
			break;
		case ROTATE_LEFT:
			player.rotatingLeft = false;
			break;
		case ROTATE_RIGHT:
			player.rotatingRight = false;
			break;
		case SHOOT:
			player.canShoot = false;
			break;
		}
	}
}

void ofApp::adjustDifficulty(int level) {
	float newSpawnRate;
	float newAgentSpeed;
	float newAgentTurningSpeed;
	float newAgentLifeSpan;
	int newNAgents;

	// Set the parameters based on difficulty level
	switch (level) {
	case 1: // Easy
		newSpawnRate = 0.5f;
		newAgentSpeed = 1.0f;
		newAgentTurningSpeed = 0.5f;
		newAgentLifeSpan = 10.0f;
		newNAgents = 5;
		break;
	case 2: // Medium
		newSpawnRate = 1.0f;
		newAgentSpeed = 1.5f;
		newAgentTurningSpeed = 1.0f;
		newAgentLifeSpan = 5.0f;
		newNAgents = 3;
		break;
	case 3: // Hard
		newSpawnRate = 2.0f;
		newAgentSpeed = 2.0f;
		newAgentTurningSpeed = 1.5f;
		newAgentLifeSpan = 3.0f;
		newNAgents = 1;
		break;
	}

	// Call the listener callbacks to apply the new settings
	onSpawnRateChanged(newSpawnRate);
	onAgentSpeedChanged(newAgentSpeed);
	onAgentTurningSpeedChanged(newAgentTurningSpeed);
	onAgentLifeSpanChanged(newAgentLifeSpan);
	onNAgentsChanged(newNAgents);

	// Update the GUI to reflect the new settings
	spawnRateParam.set(newSpawnRate);
	agentSpeedParam.set(newAgentSpeed);
	agentTurningSpeedParam.set(newAgentTurningSpeed);
	agentLifeSpanParam.set(newAgentLifeSpan);
	nAgentsParam.set(newNAgents);
}

void ofApp::difficultyChanged(int& level) {
	bDifficultyChanged = true;
}

// Listener callbacks for GUI parameters

void ofApp::onPlayerScaleChanged(float& scale) {
	player.setScale(scale);
}

void ofApp::onPlayerMovementSpeedChanged(float& speed) {
	player.setMovementSpeed(speed);
}

void ofApp::onPlayerTurningSpeedChanged(float& turningSpeed) {
	player.setTurnSpeed(turningSpeed);
}

void ofApp::onSpawnRateChanged(float& rate) {
	agentEmitter.setSpawnRate(rate);
}

void ofApp::onAgentSpeedChanged(float& speed) {
	agentEmitter.setAgentSpeed(speed);
}

void ofApp::onAgentTurningSpeedChanged(float& turningSpeed) {
	agentEmitter.setAgentTurningSpeed(turningSpeed);
}

void ofApp::onAgentLifeSpanChanged(float& lifespan) {
	agentEmitter.setLifeSpan(lifespan);
}

void ofApp::onNAgentsChanged(int& nAgents) {
	agentEmitter.setNAgents(nAgents);
}

void ofApp::restartGame() {
	float currentTime = ofGetElapsedTimef(); // Reset game timer
	player.setup(ofGetWidth() / 2, ofGetHeight() / 2, player.getMovementSpeed(), player.getTurnSpeed());
	player.energy = 100; // Reset player energy
	agentEmitter.reset(currentTime); // Reset the emitter, including the lastSpawnTime within it
	gameTime = currentTime; // Reset the game time
	gameStarted = true; // Start the game
	isGameOver = false; // Game is no longer over
}

void ofApp::toggleAgentSprite() {
	// Loop through all agents and toggle their sprite state
	for (auto& agent : agentEmitter.getAgents()) {
		Agent::drawSpriteMode = !Agent::drawSpriteMode;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
