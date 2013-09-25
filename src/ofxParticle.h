//
//  ofxParticle.h
//  ofxParticlesExample
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
        ofxParticle(ofVec3f pos, ofVec3f vel, float size_, float life_, int maxHistoryLength_);
        ofxParticle(const ofxParticle& mom);
        
        ~ofxParticle();
    
        bool operator < (const ofxParticle& b);

        ofxParticle& operator = (const ofxParticle& mom);
        
        void applyForce(const ofVec3f& force);
    
        void attractTo(const ofxParticle& p, float acc, float minDist, bool bConsumeParticle);
        void attractTo(const ofPoint& pt, float acc, float minDist, bool bConsumeParticle);
            
        void gravitateTo(const ofxParticle& p, float gravity, float minDist, bool bConsumeParticle);
        void gravitateTo(const ofPoint& pt, float gravity, float mass2, float minDist, bool bConsumeParticle);
        
        void rotateAround(const ofxParticle& p, float acc, float minDist, bool bConsumeParticle);
        void rotateAround(const ofPoint& pt, float acc, float minDist, bool bConsumeParticle);
            
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
        int maxHistoryLength;
        float dt;
        int particleID;
    
    private:
        deque<ofVec3f> history;
};