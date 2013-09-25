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
: size(1.0f)
, sizeSpread(0.0f)
, life(1.0f)
, lifeSpread(0.0f)
, particleMaxHistoryLength(0)
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
void ofxParticleEmitter::setPosition(const ofVec3f& pos)
{
    positionStart = positionEnd = pos;
}

//--------------------------------------------------------------
void ofxParticleEmitter::setPosition(const ofVec3f& posStart, const ofVec3f& posEnd)
{
    positionStart = posStart;
    positionEnd = posEnd;
}

//--------------------------------------------------------------
void ofxParticleEmitter::setVelocity(const ofVec3f& vel)
{
    velocityStart = velocityEnd = vel;
}

//--------------------------------------------------------------
void ofxParticleEmitter::setVelocity(const ofVec3f& velStart, const ofVec3f& velEnd)
{
    velocityStart = velStart;
    velocityEnd = velEnd;
}
