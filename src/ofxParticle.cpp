//
//  ofxParticle.cpp
//  ofxParticlesExample
//
//  Created by Elie Zananiri on 2013-09-17.
//  Based on ofxParticles by Timothy Scaffidi, 2012-06-14.
//

#include "ofxParticle.h"
#include "SMSettings.h"

const float HEAT_SPAWN_AMT = .1f;
const float HEAT_KILL_THRESHOLD = 0.05f;
const double HEAT_CHANGE_RATE = 0.04;
const float MIN_RADIUS = 8.0f;
const float MAX_RADIUS = 60.0f;

//--------------------------------------------------------------
ofxParticle::ofxParticle()
{
    emitterID = -1;
    
    position = ofVec4f(0,0,0,HEAT_SPAWN_AMT);
    velocity = acceleration = ofVec3f(0,0,0);
    color = ofColor(255,255,255,255);
    mass = 1.0;
    size = 1.0;
    lifeStart = life = 1.0;
    particleID = 0;
    texID = 0;
    dt = 1.0/60;
    
    history.push_back(position);
}

//--------------------------------------------------------------
ofxParticle::ofxParticle(ofVec3f pos, ofVec3f vel, float size_, float life_, int maxHistoryLength_)
{
    position = pos;
    velocity = vel;
    acceleration = ofVec3f(0,0,0);
    color = ofColor(255,255,255,255);
    startColor = color;
    mass = 1.0;
    size = size_;
    maxHistoryLength = maxHistoryLength_;
    lifeStart = life = MAX(1.0, life_);
    particleID = 0;
    texID = 0;
    dt = 1.0/60;
}

//--------------------------------------------------------------
ofxParticle::ofxParticle(const ofxParticle &mom)
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
    texID = 0;
    dt = 1.0f / 60.0f;
}

//--------------------------------------------------------------
ofxParticle::~ofxParticle()
{
    history.clear();
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
    acceleration += force * dt;
}

//--------------------------------------------------------------
void ofxParticle::attractTo(const ofxParticle& p, float acc, float minDist, bool bConsumeParticle)
{
    attractTo(p.position, acc, minDist, bConsumeParticle);
}

//--------------------------------------------------------------
void ofxParticle::attractTo(const ofPoint& pt, float acc, float minDist, bool bConsumeParticle)
{
    ofVec3f dir = pt - position;

    float dist = dir.length();
    if (dist < minDist) {
        dist = minDist;
        if (bConsumeParticle) {
            life = 0;
        }
    }
    
    dir.normalize().scale(acc * dt);
    acceleration += dir;
}

//--------------------------------------------------------------
void ofxParticle::gravitateTo(const ofxParticle& p, float gravity, float minDist, bool bConsumeParticle)
{
    gravitateTo(p.position, gravity, p.mass, minDist, bConsumeParticle);
}

//--------------------------------------------------------------
void ofxParticle::gravitateTo(const ofPoint& pt, float gravity, float mass2, float minDist, bool bConsumeParticle)
{
    if (pt == position) return;
    
    ofVec3f dir = pt - position;

    float dist = dir.length();
    if (dist < minDist) {
        dist = minDist;
        if (bConsumeParticle) {
            life = 0;
        }
    }
    
    dir.normalize().scale(gravity * mass * mass2 * dt * (1.0f / dist));
    acceleration += dir;
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
    if(history.size() > 0) {
        ofVec4f curParticle = history.back();
        if (curParticle[3] < HEAT_KILL_THRESHOLD) {
            history.pop_front();
        }
    
        if (inView(curParticle)) {
            curParticle[3] = std::min(static_cast<float>(curParticle[3] + HEAT_CHANGE_RATE), 1.0f);
        } else {
            curParticle[3] = std::max(static_cast<float>(curParticle[3] - HEAT_CHANGE_RATE), 0.0f);
        }
        position[3] = curParticle[3];
    }
    
    dt = timeStep;
    velocity += acceleration * dt;
    velocity -= (velocity * dt * (1.0 - drag));
    position += velocity * dt;
    acceleration -= acceleration * dt;
    rotation += rotationalVelocity * dt;
    
//    color.a = life/lifeStart*startColor.a;
    
    life -= dt;
    if (life < 0) life = 0;
    
    if (maxHistoryLength > 0) {
        history.push_back(position);
        if (history.size() > maxHistoryLength) {
            history.pop_front();
        }
    }
}

//--------------------------------------------------------------
bool ofxParticle::inView(ofVec4f& pos)
{
    return pos[0] >= kDisplayMinX && pos[0] <= kDisplayMaxX &&
           pos[1] >= kDisplayMinY && pos[1] <= kDisplayMaxY &&
           pos[2] >= kDisplayMinZ && pos[2] <= kDisplayMaxZ;
}

//--------------------------------------------------------------
void ofxParticle::draw()
{
    ofColor c = color;
    ofSetColor(c);
    ofSetLineWidth(size);
    ofLine(position, position-velocity*dt);
    ofSetLineWidth(1.0f);
}

//--------------------------------------------------------------
void ofxParticle::drawVertex()
{
    drawVertex(color);
}

//--------------------------------------------------------------
void ofxParticle::drawVertex(ofColor color_)
{
    ofColor c = color_;
    c.a = color.a;
    ofSetColor(c);
    glVertex3f(position.x, position.y, position.z);
}

//--------------------------------------------------------------
void ofxParticle::drawHistory()
{
    if(history.size() > 0) {
        const ofVec4f back = history.back();
        float temp = static_cast<float>((size-MIN_RADIUS)/(MAX_RADIUS-MIN_RADIUS));
        float radius = size * back[3];

        ofSetLineWidth(trailThickness);
        glBegin(GL_LINE_STRIP);
        float total = history.size();
        for (int i = history.size()-1; i>0; i--) {
            float per = i / total;

            const ofVec4f& cur = history[i];
            const ofVec4f& last = history[i-1];
            ofVec3f curPos(cur[0], cur[1], cur[2]);
            ofVec3f lastPos(last[0], last[1], last[2]);

            float opacityScale = color.a/255.0f*back[3]*per;

            if (per > 0.8f) {
                float temp = (1.0f - per) / 0.2f;
                float tempScale = sqrt(temp);
                opacityScale *= tempScale;
            }

            glColor4f(color.r/255.0f, color.g/255.0f, color.b/255.0f, life/lifeStart*opacityScale);

            ofVec3f vecA = curPos;
            glVertex3f(vecA.x, vecA.y, vecA.z);
        }
        glEnd();
        
        ofSetLineWidth(1.0f);
        
    }
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
