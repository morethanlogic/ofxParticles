#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60.0);
    ofSetCircleResolution(180);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0, 0, 0);
    
    centerPt.set(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
    
    gravitation.setup(centerPt, 2000.0f, 500.0f, 25.0f, false);

    attraction.setup(centerPt, 1000.0f, 50.0f, 10.0f, false);
    attraction.bEnabled = false;
    
    repulsion.setup(centerPt, 1000.0f, 50.0f, 10.0f, false);
    repulsion.bEnabled = false;
    
    rotation.setup(ofVec3f(ofGetWidth() * 0.45, ofGetHeight() * 0.33f), 100.0f, 100.0f);
    
    vectorField.setup(ofGetWindowRect(), 100.0f, 128, 128, 3);
    
    mouseEmitter.velSpread = ofVec3f(25.0f, 25.0f);
    mouseEmitter.life = 10.0f;
    mouseEmitter.lifeSpread = 5.0f;
    mouseEmitter.numPars = 10;
    mouseEmitter.color = ofColor(200, 200, 255);
    mouseEmitter.colorSpread = ofColor(20, 20, 0);
    mouseEmitter.size = 32.0f;
    
    leftEmitter.position.set(0, ofGetHeight() / 3);
    leftEmitter.velocity.set(250.0, 0.0);
    leftEmitter.posSpread = ofVec3f(10.0, 10.0);
    leftEmitter.velSpread = ofVec3f(10.0, 10.0);
    leftEmitter.life = 20;
    leftEmitter.lifeSpread = 5.0;
    leftEmitter.numPars = 2;
    leftEmitter.color = ofColor(200, 100, 100);
    leftEmitter.colorSpread = ofColor(50, 50, 50);
    leftEmitter.size = 32;
    
    rightEmitter = leftEmitter;
    rightEmitter.position.set(ofGetWidth() - 1, ofGetHeight() * 2 / 3);
    rightEmitter.velocity.set(-250.0, 0.0);
    rightEmitter.color = ofColor(100, 100, 200);
    rightEmitter.colorSpread = ofColor(50, 50, 50);
    
    topEmitter = leftEmitter;
    topEmitter.position.set(ofGetWidth() * 2 / 3, 0);
    topEmitter.velocity.set(0.0, 150.0);
    topEmitter.color = ofColor(100, 200, 100);
    topEmitter.colorSpread = ofColor(50, 50, 50);
    
    botEmitter = leftEmitter;
    botEmitter.position.set(ofGetWidth() / 3, ofGetHeight() - 1);
    botEmitter.velocity.set(0.0, -150.0);
    botEmitter.color = ofColor(200, 200, 0);
    botEmitter.colorSpread = ofColor(50, 50, 0);
    
    ofLoadImage(pTex, "p.png");
    ofLoadImage(p1Tex, "p1.png");
    ofLoadImage(p2Tex, "p2.png");
    
    // Set parameter defaults.
    drag = 0.5;
    displayMode = 0;
}

//--------------------------------------------------------------
void testApp::update()
{    
    vectorField.update();
    
    // Add forces.
    float dt = MIN(ofGetLastFrameTime(), 1.0f / 10.0f);
    
    particleSystem.applyForce(gravitation);
    particleSystem.applyForce(vectorField);
    particleSystem.applyForce(rotation);
    particleSystem.applyForce(attraction);
    particleSystem.applyForce(repulsion);
    
    particleSystem.update(dt, drag);
    
    particleSystem.addParticles(leftEmitter);
    particleSystem.addParticles(rightEmitter);
    particleSystem.addParticles(topEmitter);
    particleSystem.addParticles(botEmitter);
    
    // Update mouse emitter.
    mouseVel = mousePos - prevMousePos;
    mouseVel *= 20.0f;
    if (ofGetMousePressed(0)) {
        mouseEmitter.position.set(mousePos);
        mouseEmitter.posSpread.set(mousePos - prevMousePos);
        mouseEmitter.velocity.set(mouseVel);
        mouseEmitter.velSpread.set(mouseVel - prevMouseVel);
        particleSystem.addParticles(mouseEmitter);
    }
    prevMousePos = mousePos;
    prevMouseVel = mouseVel;
}

//--------------------------------------------------------------
void testApp::draw()
{
    if (ofGetKeyPressed('v')) {
        ofSetColor(80, 80, 80);
        vectorField.debugDraw();
    }
    
    // Draw forces.
    ofNoFill();
    ofSetLineWidth(1.0);
    gravitation.debugDraw();
    rotation.debugDraw();
    if (attraction.bEnabled) {
        attraction.debugDraw();
    }
    if (repulsion.bEnabled) {
        repulsion.debugDraw();
    }
    
    // Draw system.
    ofSetLineWidth(2.0);
    particleSystem.draw();
    
    // Draw info.
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(particleSystem.numParticles) + " particles" +
                       "\n" + ofToString(ofGetFrameRate()) + " fps" +
                       "\n(G/g) gravity: " + ofToString(gravitation.strength) +
                       "\n(R/r) rotation: " + ofToString(rotation.strength) +
                       "\n(M/m) mouse attraction/repulsion: " + ofToString(attraction.strength) +
                       "\n(F/f) vector field multiplier: " + ofToString(vectorField.strength) +
                       "\n(D/d) drag constant: " + ofToString(drag) +
                       "\n(v) show vector field",
                       20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) {
        case 'r':
            if (rotation.strength > 1.1)
                rotation.strength /= 1.1;
            break;
        case 'R':
            rotation.strength *= 1.1;
            break;
            
        case 'g':
            if (gravitation.strength > 1.1)
                gravitation.strength /= 1.1;
            break;
        case 'G':
            gravitation.strength *= 1.1;
            break;
            
        case 'm':
            if (attraction.strength > 1.1)
                attraction.strength /= 1.1;
            repulsion.strength = attraction.strength;
            break;
        case 'M':
            attraction.strength *= 1.1;
            repulsion.strength = attraction.strength;
            break;
            
        case 'd':
            if(drag > 0.01)
                drag /= 1.01;
            break;
        case 'D':
            drag *= 1.01;
            if(drag > 1.0) drag = 1.0;
            break;
        case 'f':
            if (vectorField.strength > 0.1)
                vectorField.strength /= 1.1;
            break;
        case 'F':
            vectorField.strength *= 1.1;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
    mousePos.set(x, y);
    attraction.position.set(x, y);
    repulsion.position.set(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    mousePos.set(x, y);
    attraction.position.set(x, y);
    repulsion.position.set(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    if (button == 2) {
        attraction.bEnabled = true;
    }
    else if (button == 1) {
        repulsion.bEnabled = true;
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    attraction.bEnabled = false;
    repulsion.bEnabled = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    centerPt.set(w * 0.5f, h * 0.5f);
    
    vectorField.roi.set(ofRectangle(0, 0, w, h));

    leftEmitter.position.set(0, h / 3);
    rightEmitter.position.set(w - 1, h * 2 / 3);
    topEmitter.position.set(w * 2 / 3, 0);
    botEmitter.position.set(w / 3, h - 1);
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
