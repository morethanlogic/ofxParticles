//
//  ofxParticlePush.h
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-10-19.
//
//

#pragma once

#include "ofMain.h"

#include "ofxParticleForce.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticlePush
: public ofxParticleForce
{
    public:
        ofxParticlePush();
        void setup(const ofVec3f& position, float strength, float maxDist = -1.0f, float minDist = 10.0f, float bConsumeParticle = false);
        void update();
        void apply(ofxParticle * p);
        void debugDraw(int r = 0, int g = 200, int b = 0);
    
        ofVec3f lastPosition;
        ofVec3f forceDirection;
        float forceStrength;
        float maxDist;
        float minDist;
};
