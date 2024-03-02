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
		agentEmitter.update(player.position);
		player.update();
		
		// Collision detection and energy management
		for (auto& agent : agentEmitter.getAgents()) {
			if (agent.getPosition().distance(player.position) < collisionDistance) {
				player.energy -= 1; // Assuming each collision costs 1 energy
				agent.setDead(true); // Mark the agent as dead to remove it
			}
		}

		player.keepPlayerOnScreen(); // Keep the player within the screen boundaries
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
        if (key == 'w' || key == 'W') { // If "W" is pressed, move the player up
            player.setPosition(player.getPosition().x, player.getPosition().y - player.getSpeed());
        }
        if (key == 's' || key == 'S') { // If "S" is pressed, move the player down
			player.setPosition(player.getPosition().x, player.getPosition().y + player.getSpeed());
        }
        if (key == 'a' || key == 'A') { // If "A" is pressed, move the player left
			player.setPosition(player.getPosition().x - player.getSpeed(), player.getPosition().y);
        }
        if (key == 'd' || key == 'D') { // If "D" is pressed, move the player right
			player.setPosition(player.getPosition().x + player.getSpeed(), player.getPosition().y);
        }

		// Player rotation handling based on 'Q' and 'E' keys

		if (key == 'q' || key == 'Q') { // If "Q" is pressed, rotate the player left
			player.rotate(-5.0);
		}
		if (key == 'e' || key == 'E') { // If "E" is pressed, rotate the player right
			player.rotate(5.0);
		}
    }
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
