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

    videoPlayer.load("formulaOne.mp4");
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
    videoPlayer.play();

}

//--------------------------------------------------------------

void ofApp::update(){

    rpmTarget = 0;

    if (curVol >= 0.05) rpmTarget = ofMap(filterBank.getFundamentalFrequency(), midiMin, midiMax, 0, 12000);

    engine.update(rpmTarget);

    float videoSpeed = ofMap(engine.getRMP(), 0, 12000, 0, 1);

    videoPlayer.update();

}

//--------------------------------------------------------------
void ofApp::draw(){


    ofSetColor(255);
    videoPlayer.draw(0,0);

    engine.display();


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
    videoPlayer.close();
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

