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
    
        void addParticles(ofxParticleEmitter& emitter);
    
        void applyForce(ofxParticleForce& force);
        
        int update(float timeStep, float drag);
        
        void draw();
        void draw(ofTexture& tex);
        void draw(ofTexture& tex, ofTexture& tex2);
    
        list<ofxParticle *> particles;
        int numParticles;
};
