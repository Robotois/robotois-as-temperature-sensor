/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TemperatureSensor.h
 * Author: yovany
 *
 * Created on May 28, 2018, 11:21 AM
 */

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <bcm2835.h>

#define DEFAULT_ADDRESS 0x66

class TemperatureSensor {
public:
    TemperatureSensor(uint8_t addr = 0x00);
    TemperatureSensor(const TemperatureSensor& orig);
    virtual ~TemperatureSensor();
    
    float reading();
    bool deviceInfo();
private:
    uint8_t addr;
    char rBuf[20], wBuf[20];
    void bcm_init();
    void bcm_end();
    void selectModule();
    
};

#endif /* TEMPERATURESENSOR_H */

