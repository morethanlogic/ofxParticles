//
//  ofxParticleSystem.h
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#pragma once

#include <list>
#include "ofMain.h"

#include "ofxParticle.h"
#include "ofxParticleEmitter.h"
#include "ofxParticleForce.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticleSystem
{
    public:
        ofxParticleSystem();
        
        ~ofxParticleSystem();
    
        void applyForce(ofxParticleForce& force);
    
        void attractTo(const ofPoint& pt, float strength, float radius = 0, float consumeDistance = 0);
        void gravitateTo(const ofPoint& pt, float mass, float gravity, float minDist, bool bConsume = false);
        void addParticles(ofxParticleEmitter& emitter);
    
        void rotateAround(const ofPoint& pt, float acc, float minDist, float bConsumeParticle);
        void applyVectorField(float * field, int fieldWidth, int fieldHeight, int numComponents, const ofRectangle& areaOfInfluence, float force);
        
        int update(float timeStep, float drag);
        
        void draw();
        void draw(ofTexture& tex);
        void draw(ofTexture& tex, ofTexture& tex2);
    
        list<ofxParticle *> particles;
        int numParticles;
        int totalParticlesEmitted;
};
