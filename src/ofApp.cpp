#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	SpaceBackground.load(ofToDataPath("images/SpaceBackground.png"));

	// Set up the player
	player.setup(ofGetWidth() / 2, ofGetHeight() / 2, 5);
	setupKeyMap();

	// Set up the emitter
	agentEmitter.setup(ofGetWidth() / 2, ofGetHeight());
	agentEmitter.setSpawnRate(1.0);
	agentEmitter.setAgentSpeed(2.0);
	agentEmitter.setAgentTurningSpeed(0.5);
	agentEmitter.setLifeSpan(30.0);
	agentEmitter.setNAgents(1);
	agentEmitter.start();  // Start spawning agents immediately

	// GUI Setup
	gui.setup();
	gui.add(difficultyLevel.setup("Difficulty Level", 1, 1, 3));

	// Add parameters to the GUI
	playerScaleParam.set("Player Scale", 1.0, 0.5, 2.0);
	spawnRateParam.set("Agent Spawn Rate", 1.0, 0.5, 5.0);
	agentSpeedParam.set("Agent Speed", 2.0, 0.1, 3.0);
	agentTurningSpeedParam.set("Agent Turning Speed", 0.25, 0.1, 0.75);
	agentLifeSpanParam.set("Agent Life Span", 5.0, 1.0, 15.0);
	nAgentsParam.set("Number of Agents", 1, 1, 5);

	gui.add(playerScaleParam);
	gui.add(spawnRateParam);
	gui.add(agentSpeedParam);
	gui.add(agentTurningSpeedParam);
	gui.add(agentLifeSpanParam);
	gui.add(nAgentsParam);
	gui.add(showGui.setup("Show GUI", true));

	// Add listeners to the parameters
	difficultyLevel.addListener(this, &ofApp::difficultyChanged);
	playerScaleParam.addListener(this, &ofApp::onPlayerScaleChanged);
	spawnRateParam.addListener(this, &ofApp::onSpawnRateChanged);
	agentSpeedParam.addListener(this, &ofApp::onAgentSpeedChanged);
	agentTurningSpeedParam.addListener(this, &ofApp::onAgentTurningSpeedChanged);
	agentLifeSpanParam.addListener(this, &ofApp::onAgentLifeSpanChanged);
	nAgentsParam.addListener(this, &ofApp::onNAgentsChanged);

	// Game state initialization
	gameTime = ofGetElapsedTimef();
	finalGameTime = 0;
	gameStarted = false;
	isGameOver = false;
	bDifficultyChanged = false;
	difficultyHasBeenSet = false;
}

//--------------------------------------------------------------
void ofApp::update() {
	float currentElapsedTime = ofGetElapsedTimef(); // Current time since the app started

	// If the game has started and is not over, update the game state
	if (gameStarted && !isGameOver) {
		float elapsedTimeSinceStart = currentElapsedTime - gameTime; // Time since the game started

		// Update the agent emitter and player
		agentEmitter.update(elapsedTimeSinceStart, player.getPosition());
		player.update();

		// Check for collisions and update energy
		float collisionDist = collisionDistance * player.getScale();
		for (auto& agent : agentEmitter.getAgents()) {
			if (agent.getPosition().distance(player.getPosition()) < collisionDist) {
				player.decreaseEnergy();
				agent.kill();
			}
		}

		// Check if the player has run out of energy
		if (player.energy <= 0) {
			finalGameTime = elapsedTimeSinceStart;
			isGameOver = true;
			gameStarted = false;
		}
	}

	// Adjust game parameters based on difficulty level if it has been changed
	if (bDifficultyChanged) {
		adjustDifficulty(difficultyLevel);
		bDifficultyChanged = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Make SpackBackground the background image
	SpaceBackground.draw(0, 0, ofGetWidth(), ofGetHeight());

	if (gameStarted) {
		// Display ongoing game time
		float currentGameTime = ofGetElapsedTimef() - gameTime;
		player.draw();
		agentEmitter.draw();
		player.displayEnergy();
		if (showGui) {
			gui.draw();
		}
		ofDrawBitmapString("Game Time: " + ofToString(currentGameTime, 2) + " seconds", ofGetWidth() - 210, 40);
	}
	else {
		// Display game over message
		if (isGameOver) {
			ofDrawBitmapString("Game Over! Press R to restart", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
			ofDrawBitmapString("Final Game Time: " + ofToString(finalGameTime, 2) + " seconds", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 20);
		} else {
			ofDrawBitmapString("Press Space to Play", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
		}
	}
	// Display frame rate
	ofDrawBitmapString("Frame Rate: " + ofToString(ofGetFrameRate(), 2), ofGetWidth() - 180, 20);
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
			player.moveUp();
			break;
		case MOVE_DOWN:
			player.moveDown();
			break;
		case ROTATE_LEFT:
			player.rotateLeft();
			break;
		case ROTATE_RIGHT:
			player.rotateRight();
			break;
		case TOGGLE_GUI:
			showGui = !showGui;
			break;
		case TOGGLE_AGENT:
			toggleAgentSprite();
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
			player.stopMovingUp();
			break;
		case MOVE_DOWN:
			player.stopMovingDown();
			break;
		case ROTATE_LEFT:
			player.stopRotatingLeft();
			break;
		case ROTATE_RIGHT:
			player.stopRotatingRight();
			break;
			// No action needed for TOGGLE_GUI and START_GAME on key release
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
		newAgentTurningSpeed = 0.25f;
		newAgentLifeSpan = 10.0f;
		newNAgents = 1;
		break;
	case 2: // Medium
		newSpawnRate = 1.0f;
		newAgentSpeed = 2.0f;
		newAgentTurningSpeed = 0.5f;
		newAgentLifeSpan = 5.0f;
		newNAgents = 3;
		break;
	case 3: // Hard
		newSpawnRate = 2.0f;
		newAgentSpeed = 3.0f;
		newAgentTurningSpeed = 0.75f;
		newAgentLifeSpan = 3.0f;
		newNAgents = 5;
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
	player.setup(ofGetWidth() / 2, ofGetHeight() / 2, player.getSpeed());
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
