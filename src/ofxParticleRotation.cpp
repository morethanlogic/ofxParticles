//
//  ofxParticleRotation.cpp
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-10-01.
//
//

#include "ofxParticleRotation.h"

//--------------------------------------------------------------
ofxParticleRotation::ofxParticleRotation()
: ofxParticleForce()
{
    maxDist = 50.0f;
    minDist = 10.0f;
    bConsumeParticle = false;
}

//--------------------------------------------------------------
void ofxParticleRotation::setup(const ofVec3f& position, float strength, float maxDist, float minDist, float bConsumeParticle)
{
    ofxParticleForce::setup(position, strength);
    this->maxDist = maxDist;
    this->minDist = minDist;
    this->bConsumeParticle = bConsumeParticle;
}

//--------------------------------------------------------------
void ofxParticleRotation::apply(ofxParticle * p)
{
    if (p->position == position) return;
    
    ofVec3f to = p->position - position;
    ofVec3f force(-to.y, to.x, to.z);
    float dist = force.length();
    if (dist > maxDist) {
        return;
    }
    if (dist < minDist) {
        if (bConsumeParticle) {
            p->life = 0;
        }
        return;
    }
    force.normalize().scale(strength * p->mass);
    
    ofxParticleForce::apply(p, force);
}

//--------------------------------------------------------------
void ofxParticleRotation::debugDraw(int r, int g, int b)
{
//    ofxParticleForce::debugDraw(r, g, b, 128);
//    ofSetColor(r, g, b);
//    ofCircle(position, minDist);
//    ofCircle(position, maxDist);
//    
//    
    ofxParticleForce::debugDraw(r, g, b, 128);
    ofSetColor(r, g, b);
    
    ofSetCircleResolution(50);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(position);
    
    ofCircle(.0f, .0f, .0f, minDist);
    ofCircle(.0f, .0f, .0f, maxDist);
    
    ofRotate(90.0f, .0f, 1.0f, 0.0f);
    ofCircle(.0f, .0f, .0f, minDist);
    ofCircle(.0f, .0f, .0f, maxDist);
    
    ofRotate(90.0f, 1.0f, .0f, 0.0f);
    ofCircle(.0f, .0f, .0f, minDist);
    ofCircle(.0f, .0f, .0f, maxDist);
    ofPopMatrix();
}
