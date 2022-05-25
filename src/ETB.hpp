#ifndef __ETB_HPP
#define __ETB_HPP

#include <cstddef>

#include "CP.hpp"
#include "Battery.hpp"

#define STORAGE_CAPACITY 7
#define CHARGE_CAPACITY 6

// Estação de Troca de Bateria
class ETB {
  private:
    long int uid;
    CP cps[STORAGE_CAPACITY];

    void setCharging(int index, bool charging);
  public:
    ETB(long int uid);
    long int getUid();
    CP *getCps();
    int getNofStored();
    int getNofCharging();

    void attach(int index, Battery * battery);
    Battery * detach(int index);
    void startCharging(int index);
    void stopCharging(int index);
    int timeToCharged(int index);

    void update();
};

#endif
