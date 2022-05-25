#ifndef __MOTORCYCLE_HPP
#define __MOTORCYCLE_HPP

#include <string.h>
#include <cstddef>

#include "Battery.hpp"

#define MAX_SPEED 60

class Motorcycle {
  private:
    bool on; 
    char plate[8];
    float speed, velocity;
    Battery * battery;
  public:
    Motorcycle(char * plate);
    char * getPlate();
    float getSpeed();
    Battery * getBattery();

    void turnOn();
    void turnOff();
    void attach(Battery * battery);
    Battery * detach();
    void accelerate();
    void startBrake();
    void stopBrake();
};

#endif
