//
//  ofxParticle.h
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#pragma once

#include "ofMain.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticle
{
    public:
        ofxParticle();
        ofxParticle(ofVec3f position, ofVec3f velocity, float size, float life);
        ofxParticle(const ofxParticle& mom);
        
        ~ofxParticle();
    
        bool operator < (const ofxParticle& b);

        ofxParticle& operator = (const ofxParticle& mom);
        
        virtual void update(const float timeStep, const float drag);
            
        virtual void draw();
            
        bool isAlive();
    
        ofVec3f position;       // pixels
        ofVec3f velocity;       // pixels/sec
        ofVec3f acceleration;   // pixels/sec/sec
        ofColor color;
        
        ofVec3f rotation;
        ofVec3f rotationalVelocity;
        
        float mass;
        float size;
        float life;
        float lifeStart;
        float dt;
        int particleID;
        int emitterID;
};
