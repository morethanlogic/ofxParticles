//
//  ofxParticleEmitter.cpp
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#include "ofxParticleEmitter.h"

//--------------------------------------------------------------
ofxParticleEmitter::ofxParticleEmitter()
: size(1.0)
, sizeSpread(0.0)
, life(1.0)
, lifeSpread(0.0)
, numPars(1)
, color(255, 255, 255, 255)
, colorSpread(0,0,0,0)
{

}

//--------------------------------------------------------------
ofxParticleEmitter::~ofxParticleEmitter()
{

}

//--------------------------------------------------------------
ofxParticleEmitter & ofxParticleEmitter::setPosition(ofVec3f pos)
{
    positionStart = positionEnd = pos;
    return *this;
}

//--------------------------------------------------------------
ofxParticleEmitter & ofxParticleEmitter::setPosition(ofVec3f posStart, ofVec3f posEnd)
{
    positionStart = posStart;
    positionEnd = posEnd;
    return *this;
}

//--------------------------------------------------------------
ofxParticleEmitter & ofxParticleEmitter::setVelocity(ofVec3f vel)
{
    velocityStart = velocityEnd = vel;
    return *this;
}

//--------------------------------------------------------------
ofxParticleEmitter & ofxParticleEmitter::setVelocity(ofVec3f velStart, ofVec3f velEnd)
{
    velocityStart = velStart;
    velocityEnd = velEnd;
    return *this;
}
