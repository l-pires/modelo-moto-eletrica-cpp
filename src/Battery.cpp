#include "Battery.hpp"

Battery::Battery() {
  this->uid = -1;
  this->soc = 0;
  this->host = NULL;
}

Battery::Battery(long long int uid, float soc, void *host) {
  this->uid = uid;
  this->soc = soc;
  this->host = host;
}

void Battery::setUid(long long int uid) {
  if(this->uid != -1)
    throw "Cannot change the uid.";

  this->uid = uid;
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
