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
        
        void addParticles(ofxParticleEmitter& src);
        
        void attractTo(const ofPoint& pt, float acc, float minDist, bool bConsumeParticle);
        void gravitateTo(const ofPoint& pt, float gravity, float mass, float minDist, float bConsumeParticle);
        void rotateAround(const ofPoint& pt, float acc, float minDist, float bConsumeParticle);
        void applyVectorField(float * field, int fieldWidth, int fieldHeight, int numComponents, const ofRectangle& areaOfInfluence, float force);
        
        int update(float timeStep, float drag);
        
        void draw();
    
        void drawVertex();
        void drawVertex(ofColor color_);
        void drawHistory();
    
        void draw(ofTexture& tex);
        void draw(ofTexture& tex, ofTexture& tex2);
        
        list<ofxParticle *> particles;
        int numParticles;
        int totalParticlesEmitted;
};
