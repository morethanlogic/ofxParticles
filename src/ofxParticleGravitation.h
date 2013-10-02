//
//  ofxParticleGravitation.h
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-10-01.
//
//

#pragma once

#include "ofMain.h"

#include "ofxParticleForce.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticleGravitation : public ofxParticleForce
{
    public:
        ofxParticleGravitation();
        void setup(const ofVec3f& position, float gravity, float mass, float minDist = 10.0f, float bConsumeParticle = false);
        void apply(ofxParticle * p);
        void debugDraw(int r = 200, int g = 0, int b = 0);
    
        float mass;
        float minDist;
        bool bConsumeParticle;
};
