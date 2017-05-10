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
    maxHistorySize = 60;
    deltaRPM = 30;
    timerGearChange = 1;
    timeGearChange = ofGetElapsedTimef();

    gearRelation.push_back(60 / 10000);
    gearRelation.push_back(110 / 10000);
    gearRelation.push_back(160 / 10000);
    gearRelation.push_back(210 / 10000);
    gearRelation.push_back(260 / 10000);
    gearRelation.push_back(310 / 10000);


}

void Engine::update(float rpm_)
{

    rpmTarget = rpm_;
    rpm = rpm + (rpmTarget - rpm) * 0.1;

    rpmHistory.push_back(rpm);

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


    if ((avgPresent - avgPast) > deltaRPM) {

        if (ofGetElapsedTimef() - timeGearChange > timerGearChange) {

            if (gear > minGear) {
                gear--;
                timeGearChange = ofGetElapsedTimef();
            }
        }

    }

    else if ((avgPresent - avgPast) < -deltaRPM) {

        if (ofGetElapsedTimef() - timeGearChange > timerGearChange) {

            if (gear < maxGear) {
                gear++;
                timeGearChange = ofGetElapsedTimef();
            }
        }

    }

    cout << "Actual: " << avgPresent << " Pasado: " << avgPast << " Gear: " << gear << endl;

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
