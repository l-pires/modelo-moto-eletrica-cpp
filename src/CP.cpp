#include "CP.hpp"

CP::CP() {
  this->charging = false;
  this->battery = NULL;
}

bool CP::getCharging() {
  return this->charging;
}

void CP::setCharging(bool charging) {
  this->charging = charging;
}

Battery * CP::getBattery() {
  return this->battery;
}

void CP::attach(Battery *battery) {
  this->battery = battery;
}

Battery CP::detach() {
  Battery b = *this->battery;
  this->battery = NULL;
  return b;
}
