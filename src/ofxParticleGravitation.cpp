//
//  ofxParticleGravitation.cpp
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-10-01.
//
//

#include "ofxParticleGravitation.h"

//--------------------------------------------------------------
ofxParticleGravitation::ofxParticleGravitation()
: ofxParticleForce()
{
    mass = 1.0f;
    minDist = 10.0f;
    bConsumeParticle = false;
}

//--------------------------------------------------------------
void ofxParticleGravitation::setup(const ofVec3f& position, float gravity, float mass, float minDist, float bConsumeParticle)
{
    ofxParticleForce::setup(position, gravity);
    this->mass = mass;
    this->minDist = minDist;
    this->bConsumeParticle = bConsumeParticle;
}

//--------------------------------------------------------------
void ofxParticleGravitation::apply(ofxParticle * p)
{
    if (p->position == position) return;
        
    ofVec3f force = position - p->position;
    float dist = force.length();
    if (dist < minDist) {
        if (bConsumeParticle) {
            p->life = 0;
        }
        return;
    }
    force.normalize().scale(strength * p->mass * mass / (dist * dist));
    
    ofxParticleForce::apply(p, force);
}

//--------------------------------------------------------------
void ofxParticleGravitation::debugDraw(int r, int g, int b)
{
    ofxParticleForce::debugDraw(r, g, b, 128);
    ofSetColor(r, g, b);
    
    ofSetCircleResolution(50);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(position);
    
    ofCircle(.0f, .0f, .0f, minDist);
    
    ofRotate(90.0f, .0f, 1.0f, 0.0f);
    ofCircle(.0f, .0f, .0f, minDist);
    
    ofRotate(90.0f, 1.0f, .0f, 0.0f);
    ofCircle(.0f, .0f, .0f, minDist);
    ofPopMatrix();
}
