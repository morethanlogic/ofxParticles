//
//  ofxParticleVectorField.h
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-10-01.
//
//

#pragma once

#include "ofMain.h"

#include "ofxParticleForce.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxParticleVectorField
: public ofxParticleForce
{
    public:
        ofxParticleVectorField();
        void setup(const ofRectangle& roi, float strength, int width = 128, int height = 128, int numChannels = 3);
        void update();
        void apply(ofxParticle * p);
        void debugDraw(int r = 80, int g = 80, int b = 80);
    
        ofFloatPixels field;
        ofRectangle roi;
};
