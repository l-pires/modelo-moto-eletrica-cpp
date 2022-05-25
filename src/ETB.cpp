#include "ETB.hpp"

ETB::ETB(long int uid) {
  this->uid = uid;
}

long int ETB::getUid() {
  return this->uid;
}

CP * ETB::getCps() {
  return this->cps;
}

int ETB::getNofStored() {
  int n = 0;
  for(int i = 0; i < STORAGE_CAPACITY; i++)
    if(this->cps[i].getBattery() != NULL)
      n++;
  return n;
}

int ETB::getNofCharging() {
  int n = 0;
  for(int i = 0; i < STORAGE_CAPACITY; i++)
    if(this->cps[i].getCharging() == true)
      n++;
  return n;
}

void ETB::attach(int index, Battery * battery) {
  if(index < 0 || index > STORAGE_CAPACITY - 1)
    throw "Index out of range.";
  if(this->cps[index].getBattery() != NULL)
    throw "CP is occupied.";
  
  this->cps[index].attach(battery);
}

Battery ETB::detach(int index) {
  if(index < 0 || index > STORAGE_CAPACITY - 1)
    throw "Index out of range.";
  if(this->cps[index].getBattery() == NULL)
    throw "CP is empty.";
  
  return this->cps[index].detach();
}

void ETB::setCharging(int index, bool charging) {
  if(index < 0 || index > STORAGE_CAPACITY - 1)
    throw "Index out of range.";
  if(this->cps[index].getBattery() == NULL)
    throw "CP is empty.";

  this->cps[index].setCharging(charging);
}

void ETB::startCharging(int index) {
  this->setCharging(index, true);
}

void ETB::stopCharging(int index) {
  this->setCharging(index, false);
}

int ETB::timeToCharged(int index) {
  if(index < 0 || index > STORAGE_CAPACITY - 1)
    throw "Index out of range.";
  if(this->cps[index].getBattery() == NULL)
    throw "CP is empty.";
  if(!this->cps[index].getCharging())
    throw "Battery isn't charging.";
  
  return this->cps[index].timeToCharged();
}