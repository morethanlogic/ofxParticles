//
//  ofxParticleEmitter.h
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#pragma once

#include "ofMain.h"

#include "ofxParticle.h"

//--------------------------------------------------------------
inline ofVec3f ofRandVec3f()
{
    return ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()).normalize().scale(ofRandomf());
}

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticleEmitter
{
    public:
        ofxParticleEmitter();
        ~ofxParticleEmitter();
    
        virtual void debugDraw(int r = 0, int g = 0, int b = 200);

        virtual list<ofxParticle *> emit();
    
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
        
        int numPars;
        
        ofColor color;
        ofColor colorSpread;
    
        int emitterID;
        bool bEnabled;
};
