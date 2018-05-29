/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yovany
 *
 * Created on May 25, 2018, 10:34 AM
 */

#include <cstdlib>
#include "TemperatureSensor.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    TemperatureSensor temp;
    temp.deviceInfo();
    float reading = temp.reading();
    return 0;
}

