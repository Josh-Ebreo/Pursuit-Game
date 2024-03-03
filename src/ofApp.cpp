#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Set up the player
    player.setup(ofGetWidth() / 2, ofGetHeight() / 2, 5);

	// Set up the emitter
	agentEmitter.setup(ofGetWidth() / 2, ofGetHeight());
	agentEmitter.setSpawnRate(1.0);
	agentEmitter.setAgentSpeed(2.0);
	agentEmitter.setLifeSpan(30.0);

	// GUI Setup
	gui.setup();
	gui.add(energy.setup("Energy", 100, 0, 100));
	gui.add(spawnRate.setup("Spawn Rate", 1.0, 0.1, 10.0));
	gui.add(agentSpeed.setup("Agent Speed", 2.0, 0.1, 10.0));
	gui.add(agentLifeSpan.setup("Life Span", 30.0, 1.0, 100.0));
	gui.add(showGui.setup("Show GUI", true));

	// Game state initialization
	gameTime = 0;
	gameStarted = false;

}

//--------------------------------------------------------------
void ofApp::update(){
	if (gameStarted) {
		// Update the state of the emitter and player
		agentEmitter.update(player.position);
		player.update();
		
		// Collision detection and energy management
		for (auto& agent : agentEmitter.getAgents()) {
			if (agent.getPosition().distance(player.position) < collisionDistance) {
				player.energy -= 1; // Assuming each collision costs 1 energy
				agent.setDead(true); // Mark the agent as dead to remove it
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	if (gameStarted) {
		player.draw();
		agentEmitter.draw();

		// Draw other game elements like energy bar, game time, etc.
	}

	if (showGui) {
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') { // If spacebar is pressed, start the game
		gameStarted = true;
		gameTime = 0;
		player.setup(ofGetWidth() / 2, ofGetHeight() / 2, 5); // Reset player position and speed
		agentEmitter.start(); // Start spawning agents
	}

    // Player movement handling based on "WASD" keys
    if (gameStarted) {
		// Set movement flags
		if (key == 'w' || key == 'W') {
			player.moveUp();
		}
		if (key == 's' || key == 'S') {
			player.moveDown();
		}
		if (key == 'a' || key == 'A') { 
			player.rotateLeft();
		}
		if (key == 'd' || key == 'D') {
			player.rotateRight();
		}
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// Unset movement flags
	if (key == 'w' || key == 'W') {
		player.stopMovingUp();
	}
	if (key == 's' || key == 'S') {
		player.stopMovingDown();
	}
	if (key == 'a' || key == 'A') {
		player.stopRotatingLeft();
	}
	if (key == 'd' || key == 'D') {
		player.stopRotatingRight();
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
