//
//  ofxParticle.h
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//
//

#pragma once

#include "ofMain.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticle
{
    public:
        ofxParticle();
        ofxParticle(ofVec3f pos, ofVec3f vel, float size_, float life_);
        ofxParticle(const ofxParticle &mom);
        
        ~ofxParticle();
    
        bool operator < (const ofxParticle &b);

        ofxParticle & operator=(const ofxParticle &mom);
        
        void applyForce(ofVec3f force);
    
        void attractTo(ofxParticle p, const float accel, const float minDist, const bool consumeParticle);
        void attractTo(ofPoint p, const float accel, const float minDist, const bool consumeParticle);
            
        void gravitateTo(ofxParticle p, const float gravity, const float minDist, const bool consumeParticle);
        void gravitateTo(ofPoint p, const float gravity, const float mass2, const float minDist, const bool consumeParticle);
        
        void rotateAround(ofxParticle p, const float accel, const float minDist, const bool consumeParticle);
        void rotateAround(ofPoint p, const float accel, const float minDist, const bool consumeParticle);
            
        void update(const float timeStep, const float drag);
            
        void draw();
        void draw(ofTexture & tex);
            
        bool isAlive();
    
        ofVec3f position;
        ofVec3f velocity; // pixels/sec
        ofVec3f acceleration; // pixels/sec/sec
        ofColor color;
        
        ofVec3f rotation;
        ofVec3f rotationalVelocity;
        
        float mass;
        float size;
        float life;
        float lifeStart;
        float dt;
        int particleID;
};