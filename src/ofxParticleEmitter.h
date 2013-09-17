//
//  ofxParticleEmitter.h
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//
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
        
        ofxParticleEmitter & setPosition(ofVec3f pos);
        ofxParticleEmitter & setPosition(ofVec3f posStart, ofVec3f posEnd);
        
        ofxParticleEmitter & setVelocity(ofVec3f vel);
        ofxParticleEmitter & setVelocity(ofVec3f velStart, ofVec3f velEnd);
        
        ofVec3f positionStart;
        ofVec3f positionEnd;
        ofVec3f posSpread;
        
        ofVec3f velocityStart;
        ofVec3f velocityEnd;
        ofVec3f velSpread;
        
        ofVec3f rotation;
        ofVec3f rotSpread;
        ofVec3f rotVel;
        ofVec3f rotVelSpread;
        
        float size;
        float sizeSpread;
        
        float life;
        float lifeSpread;
        
        int numPars;
        
        ofColor color;
        ofColor colorSpread;
};
