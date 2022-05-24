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
