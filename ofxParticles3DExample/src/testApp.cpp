#include "testApp.h"

int kBoxSize = 300;

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60.0);
    ofSetCircleResolution(180);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0, 0, 0);
    
    centerPt.set(0, 0, 0);
    
    const float velVal = 150.0;
    
    mouseEmitter.velSpread = ofVec3f(25.0f, 25.0f);
    mouseEmitter.life = 10.0f;
    mouseEmitter.lifeSpread = 5.0f;
    mouseEmitter.numPars = 10;
    mouseEmitter.color = ofColor(200, 200, 255);
    mouseEmitter.colorSpread = ofColor(20, 20, 0);
    mouseEmitter.size = 32.0f;
    
    leftEmitter.position.set(kBoxSize * -0.5, kBoxSize * -0.5, kBoxSize * 0.5);
    leftEmitter.velocity.set(velVal, velVal, -velVal);
    leftEmitter.posSpread = ofVec3f(10, 10, 10);
    leftEmitter.velSpread = ofVec3f(10.0,10);
    leftEmitter.life = 20;
    leftEmitter.lifeSpread = 5.0;
    leftEmitter.numPars = 2;
    leftEmitter.color = ofColor(200, 100, 100);
    leftEmitter.colorSpread = ofColor(50, 50, 50);
    leftEmitter.size = 32;
    
    rightEmitter = leftEmitter;
    rightEmitter.position.set(kBoxSize * 0.5, kBoxSize * -0.5, kBoxSize * -0.5);
    rightEmitter.velocity.set(-velVal, velVal, velVal);
    rightEmitter.color = ofColor(100, 100, 200);
    rightEmitter.colorSpread = ofColor(50, 50, 50);

    topEmitter = leftEmitter;
    topEmitter.position.set(kBoxSize * -0.5, kBoxSize * 0.5, kBoxSize * -0.5);
    topEmitter.velocity.set(velVal, -velVal, velVal);
    topEmitter.color = ofColor(100, 200, 100);
    topEmitter.colorSpread = ofColor(50, 50, 50);

    botEmitter = leftEmitter;
    botEmitter.position.set(kBoxSize * 0.5, kBoxSize * 0.5, kBoxSize * 0.5);
    botEmitter.velocity.set(-velVal, -velVal, -velVal);
    botEmitter.color = ofColor(200, 200, 0);
    botEmitter.colorSpread = ofColor(50, 50, 0);
    
    vectorField.allocate(128, 128, 3);
    
    ofLoadImage(pTex, "p.png");
    ofLoadImage(p1Tex, "p1.png");
    ofLoadImage(p2Tex, "p2.png");
    
    // Set parameter defaults.
    rotAcc = 4500;
    gravAcc = 13500;
    drag = 0.5;
    fieldMult = 40.0;
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
    particleSystem.gravitateTo(centerPt, gravAcc, 1.0f, 10.0f, false);
    particleSystem.rotateAround(centerPt, rotAcc, 10.0f, false);
    particleSystem.applyVectorField(vectorField.getPixels(), vectorField.getWidth(), vectorField.getHeight(), vectorField.getNumChannels(), ofGetWindowRect(), fieldMult);
    if (ofGetMousePressed(2)) {
        particleSystem.gravitateTo(mousePos, gravAcc, 1.0f, 10.0f, false);
    }
    
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
    cam.begin();
    
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
    ofCircle(centerPt, sqrt(gravAcc));
    ofSetColor(0, 0, 255, 50);
    ofCircle(centerPt, sqrt(rotAcc));
    
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
    
    cam.end();
    
    // Draw info.
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(particleSystem.numParticles) + " particles" +
                       "\n" + ofToString(ofGetFrameRate()) + " fps" +
                       "\n(G/g) gravitation: " + ofToString(gravAcc) +
                       "\n(R/r) rotational acceleration: " + ofToString(rotAcc) +
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
            if(rotAcc > 1.1)
                rotAcc /= 1.1;
            break;
        case 'R':
            rotAcc *= 1.1;
            break;
            
        case 'g':
            if(gravAcc > 1.1)
                gravAcc /= 1.1;
            break;
        case 'G':
            gravAcc *= 1.1;
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
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    mousePos.set(x, y);    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
//    centerPt.set(w * 0.5f, h * 0.5f);

//    leftEmitter.setPosition(ofVec3f(0,h/3));
//    rightEmitter.setPosition(ofVec3f(w-1,h*2/3));
//    topEmitter.setPosition(ofVec3f(w*2/3,0));
//    botEmitter.setPosition(ofVec3f(w/3,h-1));
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
