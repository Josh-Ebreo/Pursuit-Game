#pragma once

#include "ofMain.h"
#include "Player.h"
#include "Emitter.h"
#include "Agent.h"
#include "ExplosionEmitter.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	// Game Components
	Player player;
	Emitter agentEmitter;
	std::vector<ExplosionEmitter> explosions;

	// Sound Components
	ofSoundPlayer laserSound;
	ofSoundPlayer playerCollisionSound;
	ofSoundPlayer rayCollisionSound;

	ofImage SpaceBackground;

	enum PlayerAction {
		MOVE_UP,
		MOVE_DOWN,
		ROTATE_LEFT,
		ROTATE_RIGHT,
		TOGGLE_GUI,
		START_GAME,
		RESTART_GAME,
		TOGGLE,
		SHOOT
	};

	std::map<int, PlayerAction> keyMap;
	void setupKeyMap();

	// GUI Components
	ofxPanel gui;
	ofxIntSlider difficultyLevel;
	ofParameter<float> playerScaleParam;
	ofParameter<float> playerMovementSpeedParam;
	ofParameter<float> playerTurningSpeedParam;
	ofParameter<float> spawnRateParam;
	ofParameter<float> agentSpeedParam;
	ofParameter<float> agentTurningSpeedParam;
	ofParameter<float> agentLifeSpanParam;
	ofParameter<int> nAgentsParam;
	ofxToggle showGui;

	// Other game state variables
	float gameTime;
	float finalGameTime;
	bool gameStarted;
	bool isGameOver;
	bool difficultyHasBeenSet;
	bool bDifficultyChanged;
	void adjustDifficulty(int level);
	void difficultyChanged(int& level);

	// Methods for handling game state and GUI
	void initializeGui();
	void updateGameState(float currentElapsedTime);
	void drawGame();
	void drawGameOver();

	void onPlayerScaleChanged(float& scale);
	void onPlayerMovementSpeedChanged(float& speed);
	void onPlayerTurningSpeedChanged(float& turningSpeed);
	void onSpawnRateChanged(float& rate);
	void onAgentSpeedChanged(float& speed);
	void onAgentTurningSpeedChanged(float& turningSpeed);
	void onAgentLifeSpanChanged(float& lifespan);
	void onNAgentsChanged(int& nAgents);
	void restartGame();
	void toggleAgentSprite();
	void togglePlayerSprite();

	// Unused functions
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// Collision detection
	void checkPlayerAgentCollisions();
	void checkParticleAgentCollisions();

private: 
	const float collisionDistance = 15.0f; // Hard coded the distance from the player to the agents
};
