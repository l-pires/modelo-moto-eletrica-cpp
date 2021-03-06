#ifndef __CP_HPP
#define __CP_HPP

#include <cstddef>
#include "Battery.hpp"

#define CHARGE_PER_SEC 0.05

// Ponto de carga CP
class CP {
  private:
    bool charging;
    Battery *battery;
  public:
    CP();
    bool getCharging();
    void setCharging(bool charging);
    Battery *getBattery();

    void attach(Battery *battery);
    Battery * detach();
    int timeToCharged();

    void charge(float percent);
};

#endif
