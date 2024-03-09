#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Set up the player
    player.setup(ofGetWidth() / 2, ofGetHeight() / 2, 5);
	setupKeyMap();

	// Set up the emitter
	agentEmitter.setup(ofGetWidth() / 2, ofGetHeight());
	agentEmitter.setSpawnRate(1.0);
	agentEmitter.setAgentSpeed(2.0);
	agentEmitter.setLifeSpan(30.0);

	// GUI Setup
	gui.setup();
	gui.add(energy.setup("Energy", 100, 0, 100));
	gui.add(spawnRate.setup("Agent Spawn Rate", 1.0, 0.5, 5.0));
	gui.add(agentSpeed.setup("Agent Speed", 2.0, 0.1, 5.0));
	gui.add(agentLifeSpan.setup("Agent Life Span", 5.0, 1.0, 30.0)); // In seconds
	gui.add(nAgents.setup("Number of Agents", 1, 1, 10));
	gui.add(showGui.setup("Show GUI", true));

	// Game state initialization
	gameTime = 0;
	gameStarted = false;
	isGameOver = false;

}

//--------------------------------------------------------------
void ofApp::update() {
	// Check if the game is over
	if (gameStarted && !isGameOver) {
		if (player.energy <= 0) {
			isGameOver = true;
			gameStarted = false;
		}
		float elapsedTime = ofGetElapsedTimef();

		// Update the emitter properties from the GUI sliders
		agentEmitter.setSpawnRate(spawnRate);
		agentEmitter.setAgentSpeed(agentSpeed);
		agentEmitter.setLifeSpan(agentLifeSpan);
		agentEmitter.setNAgents(nAgents);  // Set the number of agents to spawn based on the GUI slider

		// Update the emitter, passing in the player's position
		agentEmitter.update(elapsedTime, player.getPosition());
		player.update();

		// Collision detection and energy management
		for (auto& agent : agentEmitter.getAgents()) {
			if (agent.getPosition().distance(player.getPosition()) < collisionDistance) {
				player.decreaseEnergy(); // Assuming each collision costs 1 energy
				agent.setDead(true); // Mark the agent as dead to remove it
			}
		}
		energy = player.energy; // Update the energy slider in the GUI
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	if (!gameStarted) {
		ofDrawBitmapString("Press Space to Play", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
	}
	if (gameStarted) {
		// Get elapsed time
		gameTime = ofGetElapsedTimef();
		player.draw();
		agentEmitter.draw();
		player.displayEnergy();
		if (showGui) {
			gui.draw();
		}
		// Print elapsed time showing only 2 decimal places



		ofDrawBitmapString("Game Time: " + ofToString(gameTime, 2) + " seconds", ofGetWidth() - 210, 40);
	}
	else if (isGameOver) {
		// Print game over message
		ofDrawBitmapString("Game Over! Press Space to restart", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
		// Print elapsed time
		ofDrawBitmapString("Game Time: " + ofToString(gameTime, 2) + " seconds", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 20);
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (keyMap.find(key) != keyMap.end()) {
		PlayerAction action = keyMap[key];

		switch (action) {
		case START_GAME:
			if (isGameOver) {
				isGameOver = false;
				player.energy = 100; // Reset player energy
			}
			gameStarted = true;
			gameTime = 0;
			player.setup(ofGetWidth() / 2, ofGetHeight() / 2, 5); // Reset player position and speed
			agentEmitter.start(); // Start spawning agents
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
