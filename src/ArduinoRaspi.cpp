#include "ArduinoRaspi.hpp"

#include <string_view>
#include <thread>
#include <sstream>
#include <vector>

static gpiod::chip& getChip(){
    static gpiod::chip chip{"gpiochip0"};
    return chip;
}

static std::string_view getConsumer(){
    std::stringstream ss;
    ss << std::this_thread::get_id();
    static std::string consumer = ss.str();
    return consumer;
}

static gpiod::line& getLine(uint64_t ID){
    static std::vector<gpiod::line> lines;
    static std::vector<uint64_t> line_numbers;

    for (uint64_t i = 0;i < line_numbers.size();i++){
        if(line_numbers[i] == ID){return lines[i];};
    }

    lines.emplace_back(getChip().get_line(ID));
    line_numbers.emplace_back(ID);
    return lines.back();
}

void delay(uint64_t milliSeconds){
    std::this_thread::sleep_for( std::chrono::milliseconds(milliSeconds) );
}

void pinMode(uint64_t pin, uint8_t value){
    auto line = getLine(pin);

    gpiod::line_request req;
    switch(value){
        case(OUTPUT):
            req.request_type = gpiod::line_request::DIRECTION_OUTPUT;
            break;
        case(INPUT):
            req.request_type = gpiod::line_request::DIRECTION_INPUT;
            break;
        default:
            req.request_type = gpiod::line_request::DIRECTION_AS_IS;
            break;
    }
    req.consumer = getConsumer();

    line.request(req);
}

void digitalWrite(uint64_t pin, uint8_t value){
    auto line = getLine(pin);

    if(!line.is_requested()){
        pinMode(pin,OUTPUT);
    }

    line.set_value(value);
}

uint8_t digitalRead(uint64_t pin){
    auto line = getLine(pin);

    if(!line.is_requested()){
        pinMode(pin,INPUT);
    }

    return line.get_value() == 0 ? LOW : HIGH;
}

byte shiftIn(uint64_t dataPin, uint64_t clockPin, uint8_t bitOrder){
    byte value = 0b0;

    for(uint8_t i = 0;i < 8;i++){
        byte shiftAmount = bitOrder == LSBFIRST ? i :7-i;
        byte in = digitalRead(dataPin) != LOW ? 0b1 : 0b0;
        value |= in << shiftAmount;

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }

    return value;
}

void shiftOut(uint64_t dataPin, uint64_t clockPin, uint8_t bitOrder, byte value){
    for(uint8_t i = 0;i < 8;i++){
        byte mask = bitOrder == LSBFIRST ? 0b1 << i : 0b1 << (7-i);
        digitalWrite(dataPin, !!(value & mask) );
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

