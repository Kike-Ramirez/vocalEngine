#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(54, 54, 54);
	ofSetFrameRate(60);

    int ticksPerBuffer = 8;
    bufferSize = BUFFER_SIZE; //pdBlock-64
    inChan  = 2;
	outChan = 0;
	sampleRate = SR;

    midiMin = 55;
    midiMax = 83;
    
    filterBank.setup(bufferSize, midiMin, midiMax, inChan, BANDWITH, sampleRate, 1.0);
    filterBank.setColor(ofColor::orange);

    soundStream.setup(this, outChan, inChan, sampleRate, bufferSize, ticksPerBuffer);
    rpm = 0;

    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);

    bufferCounter	= 0;

    engine.setup();

}

//--------------------------------------------------------------

void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){


    ofBackground(0);

    rpmTarget = 0;

    if (curVol >= 0.02) rpmTarget = ofMap(filterBank.getFundamentalFrequency(), midiMin, midiMax, 0, -270);


    engine.update(rpmTarget);

    string texto = ofToString(filterBank.getFundamentalFrequency());
    cout << texto << endl;

    rpm = rpm + (rpmTarget - rpm) * 0.1;

    // ofDrawBitmapString(texto, 20, 20);

    //ofDrawRectangle(ofGetWidth() * 0.3, ofGetHeight() - rpm, ofGetWidth() * 0.4, rpm );

    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    ofSetColor(255);
    ofNoFill();
    ofDrawCircle(0, 0, 400);
    ofRotate(rpm);
    ofSetLineWidth(3);
    ofDrawLine(0, 0, 300, 0);
    ofSetLineWidth(1);
    ofPopMatrix();



}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    //Analyze Input Buffer with ofxFilterbank
    filterBank.analyze(input);

    curVol = 0.0;

    // samples are "interleaved"
    int numCounted = 0;

    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;

        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }

    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;

    // this is how we get the root of rms :)
    curVol = sqrt( curVol );

//    smoothedVol *= 0.93;
//    smoothedVol += 0.07 * curVol;

    bufferCounter++;

    
}


void ofApp::audioOut(float * output, int bufferSize, int nChannels){

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    switch (key){
        case 'q':
            filterBank.showAll = !filterBank.showAll;
			break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void ofApp::exit(){
    soundStream.stop();
    soundStream.close();
    filterBank.exit();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

