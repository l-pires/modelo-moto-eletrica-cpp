#include <cstddef>
#include "Battery.hpp"

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
    Battery detach();
};
