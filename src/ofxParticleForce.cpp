//
//  ofxParticleForce.cpp
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-10-01.
//
//

#include "ofxParticleForce.h"

//--------------------------------------------------------------
ofxParticleForce::ofxParticleForce()
{
    bEnabled = true;
}

//--------------------------------------------------------------
void ofxParticleForce::setup(const ofVec3f& position, float strength)
{
    this->position = position;
    this->strength = strength;
}

//--------------------------------------------------------------
void ofxParticleForce::apply(ofxParticle * p, const ofVec3f& force)
{
    p->acceleration += force * p->dt;
}

//--------------------------------------------------------------
void ofxParticleForce::debug()
{
    ofCircle(position, sqrt(strength));
}
