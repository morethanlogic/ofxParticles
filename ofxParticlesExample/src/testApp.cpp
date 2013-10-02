#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60.0);
    ofSetCircleResolution(180);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0, 0, 0);
    
    centerPt.set(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
    
    gravitation.setup(centerPt, 200.0f, 50.0f, 25.0f, false);

    attraction.setup(centerPt, 100.0f, 50.0f, 10.0f, false);
    attraction.bEnabled = false;
    
    repulsion.setup(centerPt, 100.0f, 50.0f, 10.0f, false);
    repulsion.bEnabled = false;
    
    rotation.setup(ofVec3f(ofGetWidth() * 0.45, ofGetHeight() * 0.33f), 5.0f, 100.0f);
    
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
    
    vectorField.allocate(128, 128, 3);
    
    ofLoadImage(pTex, "p.png");
    ofLoadImage(p1Tex, "p1.png");
    ofLoadImage(p2Tex, "p2.png");
    
    // Set parameter defaults.
    drag = 0.5;
    fieldMult = 5.0f;
    displayMode = 0;
}

//--------------------------------------------------------------
void testApp::update()
{    
    // Update vector field.
    for (int y = 0; y < vectorField.getHeight(); y++) {
        for (int x = 0; x< vectorField.getWidth(); x++) {
            int index = vectorField.getPixelIndex(x, y);
            float angle = ofNoise(x / (float)vectorField.getWidth() * 4.0f, y / (float)vectorField.getHeight() * 4.0f, ofGetElapsedTimef() * 0.05f) * TWO_PI * 2.0f;
            ofVec2f dir(cos(angle), sin(angle));
            dir.normalize().scale(ofNoise(x / (float)vectorField.getWidth() * 4.0f, y / (float)vectorField.getHeight() * 4.0f, ofGetElapsedTimef() * 0.05 + 10.0f));
            vectorField.setColor(x, y, ofColor_<float>(dir.x, dir.y, 0.0f));
        }
    }
    
    // Add forces.
    float dt = MIN(ofGetLastFrameTime(), 1.0f / 10.0f);
    
    particleSystem.applyForce(gravitation);
    particleSystem.applyVectorField(vectorField.getPixels(), vectorField.getWidth(), vectorField.getHeight(), vectorField.getNumChannels(), ofGetWindowRect(), fieldMult);
    particleSystem.applyForce(attraction);
    particleSystem.applyForce(repulsion);
    particleSystem.applyForce(rotation);
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
        // Draw vector field.
        ofSetLineWidth(1.0f);
        ofSetColor(80, 80, 80);
        ofPushMatrix();
        {
            ofScale(ofGetWidth() / (float)vectorField.getWidth(), ofGetHeight() / (float)vectorField.getHeight());
            for (int y = 0; y < vectorField.getHeight(); y++) {
                for (int x = 0; x< vectorField.getWidth(); x++) {
                    ofColor_<float> c = vectorField.getColor(x, y);
                    ofVec2f dir(c.r, c.g);
                    ofLine(x, y, x + dir.x, y + dir.y);
                }
            }
        }
        ofPopMatrix();
    }
    
    // Draw forces.
    ofNoFill();
    ofSetColor(255, 0, 0, 50);
    gravitation.debug();
    ofSetColor(0, 0, 255, 50);
    rotation.debug();
    if (attraction.bEnabled) {
        ofSetColor(0, 255, 0, 50);
        attraction.debug();
    }
    if (repulsion.bEnabled) {
        ofSetColor(255, 255, 0, 50);
        repulsion.debug();
    }
    
    // Draw system.
    ofSetLineWidth(2.0);
    if (displayMode == 1) {
        particleSystem.draw(pTex);
    }
    else if(displayMode == 2) {
        particleSystem.draw(p1Tex, p2Tex);
    }
    else {
        particleSystem.draw();
    }
    
    // Draw info.
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(particleSystem.numParticles) + " particles" +
                       "\n" + ofToString(ofGetFrameRate()) + " fps" +
                       "\n(G/g) gravity: " + ofToString(gravitation.strength) +
                       "\n(R/r) rotation: " + ofToString(rotation.strength) +
                       "\n(F/f) vector field multiplier: " + ofToString(fieldMult) +
                       "\n(D/d) drag constant: " + ofToString(drag) +
                       "\n(v) show vector field" +
                       "\n(1-3) particle display modes",
                       20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
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
            
        case 'd':
            if(drag > 0.01)
                drag /= 1.01;
            break;
        case 'D':
            drag *= 1.01;
            if(drag > 1.0) drag = 1.0;
            break;
        case 'f':
            if(fieldMult > 0.1)
                fieldMult /= 1.1;
            break;
        case 'F':
            fieldMult *= 1.1;
            break;
        case '1':
            displayMode = 0;
            break;
        case '2':
            displayMode = 1;
            break;
        case '3':
            displayMode = 2;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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

    leftEmitter.position.set(0, h / 3);
    rightEmitter.position.set(w - 1, h * 2 / 3);
    topEmitter.position.set(w * 2 / 3, 0);
    botEmitter.position.set(w / 3, h - 1);
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
