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
, totalParticlesEmitted(0)
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
    totalParticlesEmitted += emitter.numPars;
}

//--------------------------------------------------------------
void ofxParticleSystem::applyForce(ofxParticleForce& force)
{
    if (force.bEnabled) {
        for (auto& it : particles) {
            force.apply(it);
        }
    }
}

//--------------------------------------------------------------
void ofxParticleSystem::applyVectorField(float * field, int fieldWidth, int fieldHeight, int numComponents, const ofRectangle& areaOfInfluence, float force)
{
    for (auto& it : particles) {
        ofVec2f pos2D(it->position.x, it->position.y);
        if (areaOfInfluence.inside(pos2D)) {
            int x = (int)ofMap(pos2D.x, areaOfInfluence.getMinX(), areaOfInfluence.getMaxX(), 0, fieldWidth - 1);
            int y = (int)ofMap(pos2D.y, areaOfInfluence.getMinY(), areaOfInfluence.getMaxY(), 0, fieldHeight - 1);
            int index = (x + y * fieldWidth) * numComponents;
            ofVec2f dir(field[index], field[index + 1]);
            dir.scale(force * it->dt);
            it->applyForce(dir);
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

//--------------------------------------------------------------
void ofxParticleSystem::draw(ofTexture& tex)
{
    for (auto& it : particles) {
        it->draw(tex);
    }
}

//--------------------------------------------------------------
void ofxParticleSystem::draw(ofTexture& tex, ofTexture& tex2)
{
    for (auto& it : particles) {
        int index = it->particleID;
        if(index % 2 == 0) {
            it->draw(tex);
        }
        else {
            it->draw(tex2);
        }
    }
}
