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
    dt = 1.0f / 60.0f;
    
    return *this;
}

//--------------------------------------------------------------
void ofxParticle::applyForce(const ofVec3f& force)
{
//    acceleration += force * mass * dt;
    acceleration += force * mass;
}

//--------------------------------------------------------------
void ofxParticle::attractTo(const ofxParticle& p, float strength, float radius, float consumeDist)
{
    attractTo(p.position, strength, radius, consumeDist);
}

//--------------------------------------------------------------
void ofxParticle::attractTo(const ofPoint& pt, float strength, float radius, float consumeDist)
{
    if (pt == position) return;
    
    ofVec3f force = pt - position;

    float dist = force.length();
    if (radius > 0 && dist > radius) {
        return;
    }
    
    if (dist < consumeDist) {
        life = 0;
    }
    
    force.normalize().scale(strength);
    applyForce(force);
}

//--------------------------------------------------------------
void ofxParticle::gravitateTo(const ofxParticle& p, float gravity, float minDist, bool bConsume)
{
    gravitateTo(p.position, p.mass, gravity, minDist, bConsume);
}

//--------------------------------------------------------------
void ofxParticle::gravitateTo(const ofPoint& pt, float mass2, float gravity, float minDist, bool bConsume)
{
    if (pt == position) return;
    
    ofVec3f force = pt - position;

    float dist = force.length();
    if (dist < minDist) {
        dist = minDist;
        if (bConsume) {
            life = 0;
        }
    }
    
    force.normalize().scale(gravity * mass2 / (dist * dist));
    applyForce(force);
}

//--------------------------------------------------------------
void ofxParticle::rotateAround(const ofxParticle& p, float acc, float minDist, bool bConsumeParticle)
{
    rotateAround(p.position, acc, minDist, bConsumeParticle);
}

//--------------------------------------------------------------
void ofxParticle::rotateAround(const ofPoint& pt, float acc, float minDist, bool bConsumeParticle)
{
    ofVec3f toPoint = position - pt;
    ofVec3f dir = ofVec3f(-toPoint.y, toPoint.x, toPoint.z);
    float dist = toPoint.length();
    if (dist < minDist) {
        dist = minDist;
        if (bConsumeParticle) {
            life = 0;
        }
    }
    
    dir.normalize().scale((acc / dist) * dt);
    acceleration += dir;
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
void ofxParticle::draw(ofTexture & tex)
{
    float w = tex.getWidth();
    float h = tex.getHeight();
    if(w > h){
        h = h/w*size;
        w = size;
    }
    else{
        w = w/h*size;
        h = size;
    }
    ofSetColor(color);
    ofPushMatrix();
    ofTranslate(position);
    ofRotateX(rotation.x);
    ofRotateY(rotation.y);
    ofRotateZ(rotation.z);
    tex.draw(w*-0.5,h*-0.5,w,h);
    ofPopMatrix();
}

//--------------------------------------------------------------
bool ofxParticle::isAlive() {
    return life > 0.0;
}
