//
//  ofxParticleSystem.h
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#pragma once

#include <list>
#include "ofMain.h"

#include "ofxParticle.h"
#include "ofxParticleEmitter.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticleSystem
{
    public:
        ofxParticleSystem();
        
        ~ofxParticleSystem();
        
        void addParticles(ofxParticleEmitter & src);
        
        void attractTo(ofPoint p, const float accel, const float minDist, const bool consumeParticle);
        
        void gravitateTo(const ofPoint& pt, float gravity, float mass, float minDist, float bConsumeParticle);
        
        void rotateAround(ofPoint p, const float accel, const float minDist, const float consumeParticle);
        
        void applyVectorField(float * field, int fieldWidth, int fieldHeight, int numComponents, ofRectangle areaOfInfluence, float force);
        
        int update(float timeStep, float drag);
        
        void draw();
        void draw(ofTexture &tex);
        void draw(ofTexture &tex, ofTexture &tex2);
        
        int getNumParticles();
        
    private:
        list<ofxParticle*> particles;
        int numParticles;
        int totalParticlesEmitted;
};
