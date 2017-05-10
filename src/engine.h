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
    float rpm;
    float rpmTarget;
    float deltaRPM;     // Threshold value to change gear
    float timeGearChange, timerGearChange;
    float speed;
    float speedTarget;
    vector<float> rpmHistory;

    void setup();
    void update(float rpm_);
    float getRMP();
    int getGear();
    float getSpeed();

};

#endif // ENGINE_H
