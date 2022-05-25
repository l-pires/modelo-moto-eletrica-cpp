#include "Motorcycle.hpp"

Motorcycle::Motorcycle(char * plate) {
  strcpy(this->plate, plate);
  this->on = false;
  this->speed = 0;
  this->acceleration = 0;
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

  this->acceleration = 0.2;
}

void Motorcycle::startBrake() {
  this->acceleration = -2;
}

void Motorcycle::stopBrake() {
  if(this->acceleration < 0)
    this->acceleration = 0;
}

void Motorcycle::update() {
  // Update state of charge
  float soc;
  if(this->on) {
    float discharge = 0.01 + (this->speed/MAX_SPEED) * 
      (this->speed/MAX_SPEED) * 0.05;
    soc = this->battery->charge(-discharge);
  } else {
    soc = this->battery->charge(-0.01);
  }
  if(soc == 0) {
    this->on = false;
  }
  
  // Update movement
  if(!this->on && this->acceleration > 0)
    this->acceleration = 0;
  
  this->speed += this->acceleration;
  if(this->speed > MAX_SPEED)
    this->speed = MAX_SPEED;
  if(this->speed < 0)
    this->speed = 0;
}
