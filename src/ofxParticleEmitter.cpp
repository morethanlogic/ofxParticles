//
//  ofxParticleEmitter.cpp
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#include "ofxParticleEmitter.h"

//--------------------------------------------------------------
inline ofVec3f ofRandVec3f()
{
    return ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()).normalize().scale(ofRandomf());
}

//--------------------------------------------------------------
ofxParticleEmitter::ofxParticleEmitter()
: size(1.0f)
, sizeSpread(0.0f)
, life(1.0f)
, lifeSpread(0.0f)
, numPars(1)
, color(255, 255, 255, 255)
, colorSpread(0, 0, 0, 0)
{

}

//--------------------------------------------------------------
ofxParticleEmitter::~ofxParticleEmitter()
{

}

//--------------------------------------------------------------
list<ofxParticle *> ofxParticleEmitter::emit()
{
    // Generate new particles.
    list<ofxParticle *> particles;
    for (int i = 0; i < numPars; i++) {
        ofVec3f p = position + ofRandVec3f() * posSpread;
        ofVec3f v = velocity + ofRandVec3f() * velSpread;
        float s = size + ofRandomf() * sizeSpread;
        float l = life + ofRandomf() * lifeSpread;
        ofxParticle * particle = new ofxParticle(p, v, s, l);
        
        particle->rotation = rotation + ofRandVec3f() * rotSpread;
        particle->rotationalVelocity = rotVel + ofRandVec3f() * rotVelSpread;
//        particle->particleID = totalParticlesEmitted + i;
        
        ofColor col = color;
        if (colorSpread != ofColor(0, 0, 0, 0)) {
            col.r = ofClamp(col.r + ofRandomf() * colorSpread.r, 0, 255);
            col.g = ofClamp(col.g + ofRandomf() * colorSpread.g, 0, 255);
            col.b = ofClamp(col.b + ofRandomf() * colorSpread.b, 0, 255);
            col.a = ofClamp(col.a + ofRandomf() * colorSpread.a, 0, 255);
        }
        particle->color = col;
        
        particles.push_back(particle);
    }
    return particles;
}
