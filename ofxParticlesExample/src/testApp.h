#pragma once

#include "ofMain.h"
#include "ofxParticles.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class testApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofVec3f centerPt;
        ofVec3f mousePos;
        ofVec3f mouseVel;
        ofVec3f prevMousePos;
        ofVec3f prevMouseVel;
    
        ofxParticleSystem particleSystem;
        ofxParticleEmitter mouseEmitter, topEmitter, botEmitter, leftEmitter, rightEmitter;
        float rotAcc, gravAcc, fieldMult, drag;
        ofFloatPixels vectorField;
        
        ofTexture pTex, p1Tex, p2Tex;
        int displayMode;
};
