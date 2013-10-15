//
//  ofxParticleSystem.cpp
//  ofxParticles
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#include "ofxParticleSystem.h"

//--------------------------------------------------------------
ofxParticleSystem::ofxParticleSystem()
: numParticles(0)
{

}

//--------------------------------------------------------------
ofxParticleSystem::~ofxParticleSystem()
{

}

//--------------------------------------------------------------
void ofxParticleSystem::addParticles(ofxParticleEmitter& emitter)
{
    list<ofxParticle *> newPars = emitter.emit();
    particles.splice(particles.end(), newPars);
    numParticles += emitter.numPars;
}

//--------------------------------------------------------------
void ofxParticleSystem::applyForce(ofxParticleForce& force)
{
    if (force.bEnabled) {
        for (auto& it : particles) {
            if ((force.maskBits & it->groupBits) != 0) {
                force.apply(it);
            }
        }
    }
}

//--------------------------------------------------------------
int ofxParticleSystem::update(float timeStep, float drag)
{
    int particlesRemoved = 0;
    for (list<ofxParticle *>::iterator it = particles.begin(); it != particles.end(); it++) {
        ofxParticle * p = (*it);
        if (p->isAlive()) {
            p->update(timeStep, drag);
        }
        else {
            it = particles.erase(it);
            delete p;
            ++particlesRemoved;
        }
    }
    numParticles -= particlesRemoved;
    
    return particlesRemoved;
}

//--------------------------------------------------------------
void ofxParticleSystem::draw()
{
    for (auto& it : particles) {
        it->draw();
    }
}
