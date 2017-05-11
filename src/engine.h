#ifndef ENGINE_H
#define ENGINE_H

#include "ofMain.h"


class Engine
{
public:
    Engine();

    int gear;
    int maxGear, minGear;
    int maxHistorySize;
    vector<float> gearRelation;
    float maxRPMChange, minRPMChange;
    bool gearChange;
    float rpm;
    float rpmTarget;
    float thresholdRPM;     // Threshold value to change gear
    float timeGearChange, timerGearChange;
    float speed;
    float speedTarget;
    vector<float> rpmHistory;

    // Visualization
    ofVec2f centerA, centerB;
    float radioA, radioB;
    float longHandA, longHandB;
    ofVec2f posIndicator, sizeIndicator;
    ofTrueTypeFont fontIndicatorSmall, fontIndicatorMedium, fontIndicatorBig;

    void setup();
    void update(float rpm_);
    void display();
    float getRMP();
    int getGear();
    float getSpeed();

};

#endif // ENGINE_H
