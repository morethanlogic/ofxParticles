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
        
        void applyForce(const ofVec3f& force);
    
        void attractTo(const ofxParticle& p, float strength, float radius = 0, float consumeDist = -1);
        void attractTo(const ofPoint& pt, float strength, float radius = 0, float consumeDist = -1);
            
        void gravitateTo(const ofxParticle& p, float gravity, float minDist, bool bConsume = false);
        void gravitateTo(const ofPoint& pt, float mass2, float gravity, float minDist, bool bConsume = false);
        
        void rotateAround(const ofxParticle& p, float acc, float minDist, bool bConsumeParticle);
        void rotateAround(const ofPoint& pt, float acc, float minDist, bool bConsumeParticle);
        
        virtual void update(const float timeStep, const float drag);
            
        virtual void draw();
        virtual void draw(ofTexture & tex);
            
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