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
        
        void setPosition(const ofVec3f& pos);
        void setPosition(const ofVec3f& posStart, const ofVec3f& posEnd);
        
        void setVelocity(const ofVec3f& vel);
        void setVelocity(const ofVec3f& velStart, const ofVec3f& velEnd);
    
        int emitterID;
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
    
        int particleMaxHistoryLength;
        float particleTrailThickness;
    
        int numPars;
    
        int texID;
    
        ofColor color;
        ofColor colorSpread;
};
