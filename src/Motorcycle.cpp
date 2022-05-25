#include "Motorcycle.hpp"

Motorcycle::Motorcycle(char * plate) {
  strcpy(this->plate, plate);
  this->on = false;
  this->speed = 0;
  this->velocity = 0;
  this->battery = NULL;
}

char * Motorcycle::getPlate() {
  return this->plate;
}

float Motorcycle::getSpeed() {
  return this->speed;
}

Battery * Motorcycle::getBattery() {
  return this->battery;
}

void Motorcycle::turnOn() {
  this->on = true;
}

void Motorcycle::turnOff() {
  this->on = false;
}

void Motorcycle::attach(Battery * battery) {
  if(this->battery != NULL)
    throw "Battery slot is occupied.";
  
  this->battery = battery;
}

Battery * Motorcycle::detach() {
  if(this->battery == NULL)
    throw "Battery slot is empty.";
  
  Battery * b = this->battery;
  this->battery = NULL;
  return b;
}

void Motorcycle::accelerate() {
  if(!this->on)
    throw "Motorcycle is off.";

  this->velocity = 0.2;
}

void Motorcycle::startBrake() {
  this->velocity = -2;
}

void Motorcycle::stopBrake() {
  if(this->velocity < 0)
    this->velocity = 0;
}
