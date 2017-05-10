#include "engine.h"

Engine::Engine()
{

}


void Engine::setup()
{

    gear = 1;
    maxGear = 6;
    minGear = 1;
    rpm = 0;
    rpmTarget = 0;
    speed = 0;
    speedTarget = 0;
    maxHistorySize = 20;
    deltaRPMUp = 30;
    deltaRPMDown = 18;
    maxRPMChange = 6000;
    minRPMChange = 2000;
    gearChange = false;

    gearRelation.push_back(60 / 10000);
    gearRelation.push_back(110 / 10000);
    gearRelation.push_back(160 / 10000);
    gearRelation.push_back(210 / 10000);
    gearRelation.push_back(260 / 10000);
    gearRelation.push_back(310 / 10000);

    // Visualization
    centerA = ofVec3f(ofGetWidth() * 0.25, ofGetHeight() * 0.5);
    centerB = ofVec3f(ofGetWidth() * 0.75, ofGetHeight() * 0.5);
    radioA = ofGetWidth() * 0.2;
    radioB = ofGetWidth() * 0.2;
    longHandA = radioA * 0.8;
    longHandB = radioB * 0.8;
    posIndicator = ofVec3f(ofGetWidth() * 0.45, ofGetHeight() * 0.2);
    sizeIndicator = ofVec3f(ofGetWidth() * 0.1, ofGetHeight() * 0.1);
    fontIndicatorSmall.loadFont("American Captain Patrius 02 FRE.ttf", 10);
    fontIndicatorMedium.loadFont("digital-7.ttf", 48);
    fontIndicatorBig.loadFont("digital-7.ttf", 78);


}

void Engine::update(float rpm_)
{

    rpmTarget = rpm_;
    rpm = rpm + (rpmTarget - rpm) * 0.05;

    if (rpm < 1) rpm = 0;

    rpmHistory.push_back(rpmTarget);

    if (rpmHistory.size() > maxHistorySize) {

        rpmHistory.erase(rpmHistory.begin());

    }

    float avgPresent = 0;

    for (int i = 0; i < 0.5 * maxHistorySize; i++) {

        avgPresent += rpmHistory[i];

    }

    avgPresent = avgPresent / (0.5 * maxHistorySize);

    float avgPast = 0;

    for (int i = 0.5 * maxHistorySize; i < maxHistorySize; i++) {

        avgPast += rpmHistory[i];

    }

    avgPast = avgPast / (0.5 * maxHistorySize);


    if ((gearChange == false) && (avgPresent == 0) && (rpm > minRPMChange) && (rpm < maxRPMChange)) {

        gearChange = true;

    }

    else if ((gearChange == true) && (avgPresent > 0) && (rpm > minRPMChange) && (rpm < maxRPMChange))
    {

        gearChange = false;

        if (gear < maxGear) gear++;
    }

    if (avgPresent == 0) {

        if ((rpm < 1000) && (gear > minGear)) {

            rpm = 4000;
            gear--;

        }
    }

    cout << "RPM: " << rpm << " Gear: " << gear << endl;

    speed = rpm * gearRelation[gear - 1];

}

float Engine::getRMP()
{
    return rpm;
}

int Engine::getGear()
{
    return gear;

}

float Engine::getSpeed()
{
    return speed;

}

void Engine::display()
{

    ofSetColor(255);
    ofSetLineWidth(3);
    ofSetCircleResolution(60);
    ofNoFill();

    // Dibujamos reloj A (RPM)
    ofPushMatrix();
    ofTranslate(centerA);
    ofSetColor(20);
    ofFill();
    ofDrawCircle(ofVec3f(0,0), 1 * radioA);
    ofSetColor(255);
    string textA = "RPM (x1000)";
    ofRectangle rectA = fontIndicatorSmall.getStringBoundingBox(textA, 0,0);
    fontIndicatorSmall.drawString(textA, 0 - 0.5 * rectA.width, -0.6 * radioA + 0.5 * rectA.height);
    ofRectangle rectDataA = fontIndicatorMedium.getStringBoundingBox(ofToString(int(rpm)), 0,0);
    fontIndicatorMedium.drawString(ofToString(int(rpm)), 0 - 0.5 * rectDataA.width, -0.4 * radioA + 0.5 * rectDataA.height);
    ofNoFill();
    ofDrawCircle(ofVec3f(0,0), 1 * radioA);
    float angleA = ofMap(rpm, 0, 12000, 25, 335);
    ofRotate(angleA);
    ofSetLineWidth(5);
    ofSetColor(255, 51, 0);
    ofDrawLine(0, 0, 0, longHandA);
    ofPopMatrix();

    // Dibujamos reloj B (Speed)
    ofPushMatrix();
    ofTranslate(centerB);
    ofSetLineWidth(3);
    ofSetColor(20);
    ofFill();
    ofDrawCircle(ofVec3f(0,0), 1 * radioB);
    ofSetColor(255);
    string textB = "kmph";
    ofRectangle rectB = fontIndicatorSmall.getStringBoundingBox(textB, 0,0);
    fontIndicatorSmall.drawString(textB, 0 - 0.5 * rectB.width, -0.6 * radioB + 0.5 * rectB.height);
    ofRectangle rectDataB = fontIndicatorMedium.getStringBoundingBox(ofToString(int(speed)), 0,0);
    fontIndicatorMedium.drawString(ofToString(int(speed)), 0 - 0.5 * rectDataB.width, -0.4 * radioB + 0.5 * rectDataB.height);
    ofNoFill();
    ofDrawCircle(ofVec3f(0,0), 1 * radioB);
    float angleB = ofMap(speed, 0, 310, 25, 335);
    ofRotate(angleB);
    ofSetLineWidth(5);
    ofSetColor(255, 51, 0);
    ofDrawLine(0, 0, 0, longHandB);
    ofPopMatrix();

    // Dibujamos indicador Velocidades (gear)
    ofPushMatrix();
    ofSetColor(20);
    ofFill();
    ofTranslate(posIndicator);
    ofSetLineWidth(3);
    ofDrawRectRounded(0, 0, sizeIndicator.x, sizeIndicator.y, 20);
    ofSetColor(255);
    ofNoFill();
    ofDrawRectRounded(0, 0, sizeIndicator.x, sizeIndicator.y, 20);
    ofFill();
    ofSetColor(0, 255, 0);
    string labelIndicator = "gear";
    ofRectangle rectLabelIndicator = fontIndicatorSmall.getStringBoundingBox(labelIndicator, 0,0);
    fontIndicatorSmall.drawString(labelIndicator, 0.5 * sizeIndicator.x - 0.5 * rectLabelIndicator.width, 0.15 * sizeIndicator.y + 0.5 * rectLabelIndicator.height);
    string textIndicator = ofToString(gear);
    ofRectangle rectIndicator = fontIndicatorMedium.getStringBoundingBox(textIndicator, 0,0);
    fontIndicatorMedium.drawString(textIndicator, 0.5 * sizeIndicator.x - 0.5 * rectIndicator.width, 0.6 * sizeIndicator.y + 0.5 * rectIndicator.height);
    ofPopMatrix();

    // Indicators

    // if ((gearChange == false) && (avgPresent > 0) && (rpm > minRPMChange) && (rpm < maxRPMChange) && (ofGetElapsedTimeMillis() % 1000 > 500) ) {
    if (ofGetElapsedTimeMillis() % 1000 > 500) {
        ofSetColor(255, 0, 0);
        string message = "Sube de Marcha";
        ofRectangle rectMessage = fontIndicatorBig.getStringBoundingBox(message, 0,0);
        fontIndicatorBig.drawString(message, 0.5 * ofGetWidth() - 0.5 * rectMessage.width, 0.5 * ofGetHeight() + 0.5 * rectMessage.height);
    }

}
