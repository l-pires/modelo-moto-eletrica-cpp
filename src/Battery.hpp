#ifndef __BATTERY_HPP
#define __BATTERY_HPP

#include <cstddef>

#define MAX_SOC 100

class Battery {
  private:
    long long int uid;
    float soc;
    void *host;
  public:
    Battery();
    Battery(long long int uid, float soc, void *host);
    void setUid(long long int uid);

    void attach(void *host);
    void detach();
    long long int getUid();
    float getSoc();
    void *getHost();

    float charge(float percent);
};

#endif
