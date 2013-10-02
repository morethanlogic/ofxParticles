//
//  ofxParticle.cpp
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#include "ofxParticle.h"

//--------------------------------------------------------------
ofxParticle::ofxParticle()
{
    position = velocity = acceleration = ofVec3f(0, 0, 0);
    color = ofColor(255, 255, 255, 255);
    mass = 1.0f;
    size = 1.0f;
    lifeStart = life = 1.0f;
    particleID = 0;
    emitterID = 0;
    dt = 1.0f / 60.0f;
}

//--------------------------------------------------------------
ofxParticle::ofxParticle(ofVec3f position, ofVec3f velocity, float size, float life)
{
    this->position = position;
    this->velocity = velocity;
    this->size = size;
    this->life = lifeStart = MAX(1.0, life);

    acceleration = ofVec3f(0, 0, 0);
    color = ofColor(255, 255, 255, 255);
    mass = 1.0;
    particleID = 0;
    emitterID = 0;
    dt = 1.0f / 60.0f;
}

//--------------------------------------------------------------
ofxParticle::ofxParticle(const ofxParticle& mom)
{
    position = mom.position;
    velocity = mom.velocity;
    acceleration = mom.acceleration;
    rotation = mom.rotation;
    rotationalVelocity = mom.rotationalVelocity;
    color = mom.color;
    mass = mom.mass;
    size = mom.size;
    life = mom.life;
    lifeStart = mom.lifeStart;
    particleID = mom.particleID;
    emitterID = mom.emitterID;
    dt = 1.0f / 60.0f;
}

//--------------------------------------------------------------
ofxParticle::~ofxParticle()
{

}

//--------------------------------------------------------------
bool ofxParticle::operator < (const ofxParticle& b)
{
    return position.z < b.position.z;
}

//--------------------------------------------------------------
ofxParticle& ofxParticle::operator = (const ofxParticle& mom)
{
    if (&mom == this) return *this;
    
    position = mom.position;
    velocity = mom.velocity;
    acceleration = mom.acceleration;
    rotation = mom.rotation;
    rotationalVelocity = mom.rotationalVelocity;
    color = mom.color;
    mass = mom.mass;
    size = mom.size;
    life = mom.life;
    lifeStart = mom.lifeStart;
    particleID = mom.particleID;
    emitterID = mom.emitterID;
    dt = 1.0f / 60.0f;
    
    return *this;
}

//--------------------------------------------------------------
void ofxParticle::update(const float timeStep, const float drag)
{
    dt = timeStep;
    velocity += acceleration * dt;
    velocity -= (velocity * dt * (1.0 - drag));
    position += velocity * dt;
    acceleration -= acceleration * dt;
    rotation += rotationalVelocity * dt;
    
    life -= dt;
    if (life < 0) life = 0;
}

//--------------------------------------------------------------
void ofxParticle::draw()
{
    ofSetColor(color, life / lifeStart * color.a);
    ofLine(position, position - velocity * dt);
}

//--------------------------------------------------------------
{
    return life > 0.0;
}
