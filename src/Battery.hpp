#ifndef __BATTERY_HPP
#define __BATTERY_HPP

#include <cstddef>

class Battery {
  private:
    long long int uid;
    float soc;
    void *host;
  public:
    Battery(long long int uid, float soc, void *host);
    void attach(void *host);
    void detach();
    long long int getUid();
    float getSoc();
    void *getHost();
};

#endif
