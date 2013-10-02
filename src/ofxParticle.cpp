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
: mass(1.0f)
, size(1.0f)
, life(1.0f)
, particleID(0)
, emitterID(0)
, groupBits(0x0001)
{
    lifeStart = life;
    dt = 1.0f / 60.0f;
}

//--------------------------------------------------------------
ofxParticle::ofxParticle(ofVec3f position, ofVec3f velocity, float size, float life)
: position(position)
, velocity(velocity)
, mass(1.0f)
, size(size)
, particleID(0)
, emitterID(0)
, groupBits(0x0001)
{
    this->life = lifeStart = MAX(1.0, life);
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
    groupBits = mom.groupBits;
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
    groupBits = mom.groupBits;
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
bool ofxParticle::isAlive()
{
    return (life > 0.0);
}
