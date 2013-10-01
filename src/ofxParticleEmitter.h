//
//  ofxParticleEmitter.h
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#pragma once

#include "ofMain.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticleEmitter
{
    public:
        ofxParticleEmitter();
        ~ofxParticleEmitter();
        ofVec3f position;
        ofVec3f posSpread;
        
        ofVec3f velocity;
        ofVec3f velSpread;
        
        ofVec3f rotation;
        ofVec3f rotSpread;
        ofVec3f rotVel;
        ofVec3f rotVelSpread;
        
        float size;
        float sizeSpread;
        
        float life;
        float lifeSpread;
        
        float numPars;
        
        ofColor color;
        ofColor colorSpread;
};
