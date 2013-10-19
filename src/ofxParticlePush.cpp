//
//  ofxParticlePush.cpp
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-10-19.
//
//

#include "ofxParticlePush.h"

//--------------------------------------------------------------
ofxParticlePush::ofxParticlePush()
: ofxParticleForce()
{
    maxDist = 50.0f;
    minDist = 10.0f;
}

//--------------------------------------------------------------
void ofxParticlePush::setup(const ofVec3f& position, float strength, float maxDist, float minDist, float bConsumeParticle)
{
    ofxParticleForce::setup(position, strength);
    this->maxDist = maxDist;
    this->minDist = minDist;
    this->lastPosition = position;
}

//--------------------------------------------------------------
void ofxParticlePush::update()
{
    forceDirection = position - lastPosition;
//    if (forceDirection.length() > forceStrength) {
        forceStrength = MAX(forceStrength, forceDirection.length());
//    }
//    else {
        forceStrength *= 0.9f;
//    }
    forceDirection.normalize();
    lastPosition = position;
}

//--------------------------------------------------------------
void ofxParticlePush::apply(ofxParticle * p)
{
    if (forceStrength == 0) {
//        cout << "not happening" << endl;
     return;
    }
    
    ofVec3f to = position - p->position;
    float dist = to.length();
    if (maxDist >= 0 && dist > maxDist) {
        return;
    }
    if (dist < minDist) {
        return;
    }
    float pct = 1.0f;
    if (maxDist > 0) {
        pct -= (dist / maxDist);  // stronger on the inside
    }
    ofVec3f force = forceDirection;
    force.scale(forceStrength * strength * p->mass * pct);
    
//    cout << "Applying force of " << force << endl;
    
    ofxParticleForce::apply(p, force);
}

//--------------------------------------------------------------
void ofxParticlePush::debugDraw(int r, int g, int b)
{
    ofxParticleForce::debugDraw(r, g, b, 128);
    ofSetColor(r, g, b);
    
    ofSetCircleResolution(50);
    ofNoFill();
    ofPushMatrix();

    ofLine(position, position + (forceDirection * forceStrength));
    
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
