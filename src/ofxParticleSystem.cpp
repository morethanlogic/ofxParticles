//
//  ofxParticleSystem.cpp
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#include "ofxParticleSystem.h"

//--------------------------------------------------------------
inline ofVec3f ofRandVec3f()
{
    return ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()).normalize().scale(ofRandomf());
}

//--------------------------------------------------------------
ofxParticleSystem::ofxParticleSystem()
: _numParticles(0)
, _totalParticlesEmitted(0)
{

}

//--------------------------------------------------------------
ofxParticleSystem::~ofxParticleSystem()
{

}

//--------------------------------------------------------------
void ofxParticleSystem::addParticles(ofxParticleEmitter& src)
{
    for (int i = 0; i < src.numPars; i++) {
        ofVec3f pos = src.positionStart;
        ofVec3f vel = src.velocityStart;
        if (src.positionEnd != src.positionStart || src.velocityStart != src.velocityEnd) {
            float rf = ofRandomuf();
            pos = src.positionStart.interpolated(src.positionEnd, rf);
            vel = src.velocityStart.interpolated(src.velocityEnd, rf);
        }
        ofVec3f p = pos + ofRandVec3f() * src.posSpread;
        ofVec3f v = vel + ofRandVec3f() * src.velSpread;
        float s = src.size + ofRandomf() * src.sizeSpread;
        float l = src.life + ofRandomf() * src.lifeSpread;
        ofxParticle * par = new ofxParticle(p,v,s,l);
        par->rotation = src.rotation+ofRandVec3f()*src.rotSpread;
        par->rotationalVelocity = src.rotVel+ofRandVec3f()*src.rotVelSpread;
        par->particleID = _totalParticlesEmitted + i;
        ofColor pColor = src.color;
        if (src.colorSpread != ofColor(0, 0, 0, 0)) {
            pColor.r = ofClamp(pColor.r + ofRandomf() * src.colorSpread.r, 0, 255);
            pColor.g = ofClamp(pColor.g + ofRandomf() * src.colorSpread.g, 0, 255);
            pColor.b = ofClamp(pColor.b + ofRandomf() * src.colorSpread.b, 0, 255);
            pColor.a = ofClamp(pColor.a + ofRandomf() * src.colorSpread.a, 0, 255);
        }
        par->color = pColor;
        _particles.push_back(par);
    }
    
    _numParticles += src.numPars;
    _totalParticlesEmitted += src.numPars;
}

//--------------------------------------------------------------
void ofxParticleSystem::attractTo(const ofPoint& pt, float acc, float minDist, bool bConsumeParticle)
{
    for (auto& it : _particles) {
        it->attractTo(pt, acc, minDist, bConsumeParticle);
    }
}

//--------------------------------------------------------------
void ofxParticleSystem::gravitateTo(const ofPoint& pt, float gravity, float mass, float minDist, float bConsumeParticle)
{
    for (auto& it : _particles) {
        it->gravitateTo(pt, gravity, mass, minDist, bConsumeParticle);
    }
}

//--------------------------------------------------------------
void ofxParticleSystem::rotateAround(const ofPoint& pt, float acc, float minDist, float bConsumeParticle)
{
    for (auto& it : _particles) {
        it->rotateAround(pt, acc, minDist, bConsumeParticle);
    }
}

//--------------------------------------------------------------
void ofxParticleSystem::applyVectorField(float * field, int fieldWidth, int fieldHeight, int numComponents, const ofRectangle& areaOfInfluence, float force)
{
    for (auto& it : _particles) {
        ofVec2f pos2D(it->position.x, it->position.y);
        if (areaOfInfluence.inside(pos2D)) {
            int x = (int)ofMap(pos2D.x, areaOfInfluence.getMinX(), areaOfInfluence.getMaxX(), 0, fieldWidth - 1);
            int y = (int)ofMap(pos2D.y, areaOfInfluence.getMinY(), areaOfInfluence.getMaxY(), 0, fieldHeight - 1);
            int index = (x + y * fieldWidth) * numComponents;
            ofVec2f dir(field[index], field[index + 1]);
            dir.scale(force);
            it->applyForce(dir);
        }
    }
}

//--------------------------------------------------------------
int ofxParticleSystem::update(float timeStep, float drag)
{
    int particlesRemoved = 0;
    for (list<ofxParticle *>::iterator it = _particles.begin(); it != _particles.end(); it++) {
        ofxParticle * p = (*it);
        if (p->isAlive()) {
            p->update(timeStep, drag);
        }
        else {
            it = _particles.erase(it);
            delete p;
            ++particlesRemoved;
        }
    }
    _numParticles -= particlesRemoved;
    
    return particlesRemoved;
}

//--------------------------------------------------------------
void ofxParticleSystem::draw()
{
    for (auto& it : _particles) {
        it->draw();
    }
}

//--------------------------------------------------------------
void ofxParticleSystem::draw(ofTexture& tex)
{
    for (auto& it : _particles) {
        it->draw(tex);
    }
}

//--------------------------------------------------------------
void ofxParticleSystem::draw(ofTexture& tex, ofTexture& tex2)
{
    for (auto& it : _particles) {
        int index = it->particleID;
        if(index % 2 == 0) {
            it->draw(tex);
        }
        else {
            it->draw(tex2);
        }
    }
}

//--------------------------------------------------------------
int ofxParticleSystem::getNumParticles()
{
    return _numParticles;
}
