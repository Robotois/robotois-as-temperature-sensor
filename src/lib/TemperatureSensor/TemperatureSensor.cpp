/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TemperatureSensor.cpp
 * Author: yovany
 *
 * Created on May 28, 2018, 11:21 AM
 */

#include "TemperatureSensor.h"
#include <bcm2835.h>
#include <stdint.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <exception>
#include <thread>
#include <chrono>

TemperatureSensor::TemperatureSensor(uint8_t _addr) {
    if (_addr > 1) {
        printf("[PhSensor] - Wrong slave address");
        return;
    }
    bcm_init();
    addr = DEFAULT_ADDRESS | _addr;
    if (!deviceInfo()) {
        printf("Error reading pH Sensor");
        return;
    }
}

TemperatureSensor::TemperatureSensor(const TemperatureSensor& orig) {
}

TemperatureSensor::~TemperatureSensor() {
}

bool TemperatureSensor::deviceInfo() {
    wBuf[0] = 'i';
    selectModule();
    bcm2835_i2c_write(wBuf, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    uint8_t result = bcm2835_i2c_read(rBuf, 20);
//    printf("First Character: %d %d\n", rBuf[0], rBuf[1]);
//    printf("Message: %s\n", rBuf);
    std::cout<<"[TempSensor] - deviceInfo: "<<std::string(rBuf)<<std::endl;
    if (rBuf[0] == 1) {
        return true;
    }
}

float TemperatureSensor::reading() {
    wBuf[0] = 'R';
    selectModule();
    bcm2835_i2c_write(wBuf, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    bcm2835_i2c_read(rBuf, 20);
    std::string message = rBuf;
//    std::string::size_type sz;
//    printf("First Character: %d\n", rBuf[6]);
    float result = -100;
    if(rBuf[0] != 0x01){
        printf("[Temp Sensor] -> Message Error\n");
        // std::this_thread::sleep_for(std::chrono::milliseconds(150));
        // bcm2835_i2c_read(rBuf, 20);
        return result;
    }
    try {
       result = std::stof(message.substr(1, 6));
    } catch (const std::exception& e) {
        // std::cout<<"[Temp Sensor] - Error: "<<e.what()<<" => Last Message: "<<message<<std::endl;
        result = -100;
//        std::cout<<"[Temp Sensor] - Last Message: "<<message<<std::endl;
    }
//    printf("Message: %.3f\n", result);
//    std::cout<<result<<std::endl;
    return result;
}

float TemperatureSensor::roundedValue(float value) {
    float newValue = std::floor((value * 100) + .5) / 100;
    return newValue;
}

void TemperatureSensor::selectModule(){
    bcm2835_i2c_setSlaveAddress(addr);
}

void TemperatureSensor::bcm_init(){
    // - 400kHz aproximadamente...
    uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_2500;
    // - La direccion del esclavo se establece en cada modulo

    if (!bcm2835_init()){
        printf("BCM2835 Error!!...\n");
        exit(1);
    }

    bcm2835_i2c_begin();

    bcm2835_i2c_setClockDivider(clk_div);
}

void TemperatureSensor::bcm_end(){
    bcm2835_i2c_end();
    bcm2835_close();
}
