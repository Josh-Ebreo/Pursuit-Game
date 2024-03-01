#pragma once

#include "ofMain.h"
#include "../Player.h"
#include "../Emitter.h"
#include "../Agent.h"
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

		// GUI Components
		ofxPanel gui;
		ofxIntSlider energy;
		ofxFloatSlider spawnRate;
		ofxFloatSlider agentLifeSpan;
		ofxFloatSlider agentSpeed;
		ofxToggle showGui;

		// Other game state variables
		float gameTime;
		bool gameStarted;

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
