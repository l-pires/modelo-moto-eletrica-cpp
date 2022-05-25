#include "Battery.hpp"

Battery::Battery(long long int uid, float soc, void *host) {
  this->uid = uid;
  this->soc = soc;
  this->host = host;
}

void Battery::attach(void *host) {
  this->host = host;
}

void Battery::detach() {
  this->host = NULL;
}

long long int Battery::getUid() {
  return this->uid;
}

float Battery::getSoc() {
  return soc;
}

void * Battery::getHost() {
  return this->host;
}

float Battery::charge(float percent) {
  this->soc += percent;
  if(this->soc > MAX_SOC)
    this->soc = MAX_SOC;
  if(this->soc < 0)
    this->soc = 0;
  
  return this->soc;
}
