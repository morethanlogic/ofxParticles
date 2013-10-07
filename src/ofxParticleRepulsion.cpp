//
//  ofxParticleRepulsion.cpp
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-10-01.
//
//

#include "ofxParticleRepulsion.h"

//--------------------------------------------------------------
ofxParticleRepulsion::ofxParticleRepulsion()
: ofxParticleForce()
{
    maxDist = 50.0f;
    minDist = 10.0f;
    bConsumeParticle = false;
}

//--------------------------------------------------------------
void ofxParticleRepulsion::setup(const ofVec3f& position, float strength, float maxDist, float minDist, float bConsumeParticle)
{
    ofxParticleForce::setup(position, strength);
    this->maxDist = maxDist;
    this->minDist = minDist;
    this->bConsumeParticle = bConsumeParticle;
}

//--------------------------------------------------------------
void ofxParticleRepulsion::apply(ofxParticle * p)
{
    if (p->position == position) return;
    
    ofVec3f force = p->position - position;
    float dist = force.length();
    if (maxDist >= 0 && dist > maxDist) {
        return;
    }
    if (dist < minDist) {
        if (bConsumeParticle) {
            p->life = 0;
        }
        return;
    }
    float pct = 1.0f;
    if (maxDist > 0) {
        pct -= (dist / maxDist);  // stronger on the inside
    }
    force.normalize().scale(strength * p->mass * pct);
    
    ofxParticleForce::apply(p, force);
}

//--------------------------------------------------------------
void ofxParticleRepulsion::debugDraw(int r, int g, int b)
{
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
