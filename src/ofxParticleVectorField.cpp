//
//  ofxParticleVectorField.cpp
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-10-01.
//
//

#include "ofxParticleVectorField.h"

//--------------------------------------------------------------
ofxParticleVectorField::ofxParticleVectorField()
: ofxParticleForce()
{

}

//--------------------------------------------------------------
void ofxParticleVectorField::setup(const ofRectangle& roi, float strength, int width, int height, int numChannels)
{
    this->strength = strength;
    this->roi = roi;
    field.allocate(width, height, numChannels);
}

//--------------------------------------------------------------
void ofxParticleVectorField::update()
{
    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getWidth(); x++) {
            int index = field.getPixelIndex(x, y);
            float angle = ofNoise(x / (float)field.getWidth() * 4.0f, y / (float)field.getHeight() * 4.0f, ofGetElapsedTimef() * 0.05f) * TWO_PI * 2.0f;
            ofVec2f dir(cos(angle), sin(angle));
            dir.normalize().scale(ofNoise(x / (float)field.getWidth() * 4.0f, y / (float)field.getHeight() * 4.0f, ofGetElapsedTimef() * 0.05 + 10.0f));
            field.setColor(x, y, ofColor_<float>(dir.x, dir.y, 0.0f));
        }
    }
}

//--------------------------------------------------------------
void ofxParticleVectorField::apply(ofxParticle * p)
{
    ofVec2f pos2D(p->position.x, p->position.y);
    if (roi.inside(pos2D)) {
        int x = (int)ofMap(pos2D.x, roi.getMinX(), roi.getMaxX(), 0, field.getWidth() - 1);
        int y = (int)ofMap(pos2D.y, roi.getMinY(), roi.getMaxY(), 0, field.getHeight() - 1);
        int index = (x + y * field.getWidth()) * field.getNumChannels();
        ofVec2f force(field[index], field[index + 1]);
        force.scale(strength);
        
        ofxParticleForce::apply(p, force);
    }
}

//--------------------------------------------------------------
void ofxParticleVectorField::debug()
{
    ofPushMatrix();
    {
        ofScale(ofGetWidth() / (float)field.getWidth(), ofGetHeight() / (float)field.getHeight());
        for (int y = 0; y < field.getHeight(); y++) {
            for (int x = 0; x < field.getWidth(); x++) {
                ofColor_<float> c = field.getColor(x, y);
                ofVec2f dir(c.r, c.g);
                ofLine(x, y, x + dir.x, y + dir.y);
            }
        }
    }
    ofPopMatrix();
}
