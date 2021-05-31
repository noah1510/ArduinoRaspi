#pragma once

#include "gpiod.hpp"

using byte = uint8_t;

const int8_t HIGH = 1;
const int8_t LOW = 0;

const int8_t OUTPUT = 1;
const int8_t INPUT = 2;

void delay(uint64_t milliSeconds);

void pinMode(uint64_t pin, uint8_t mode);
void digitalWrite(uint64_t pin, uint8_t value);
uint8_t digitalRead(uint64_t pin);

//code for shif functions
const int8_t LSBFIRST = 0;
const int8_t MSBFIRST = 1;

byte shiftIn(uint64_t dataPin, uint64_t clockPin, uint8_t bitOrder);
void shiftOut(uint64_t dataPin, uint64_t clockPin, uint8_t bitOrder, byte value);
