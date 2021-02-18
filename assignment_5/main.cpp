/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "DFRobot_RGBLCD.h"
#include <chrono>
#include <cstdio>
#define WAIT_TIME_MS 1000
#define WAIT_TIME_MS2 500  
InterruptIn Butt1(D13, PullUp);
InterruptIn Butt2(D12);
InterruptIn Butt3(D11);
InterruptIn Butt4(D10);
PwmOut buzzer(D9);

 
int on = 1, off = 0;
int butt_1 = 0;
int butt_2 = 0;
int butt_3 = 0;
int butt_4 = 0;
volatile int napp = false;
using namespace std::chrono;
Timer t;
int tid = 60;
int ned = 0;
volatile int state = true;

void start_stop(){
    
    printf("triggered!\n");
    if(napp == false){
    napp = true;
    t.start();
    }
    else if(napp == true){
    napp = false;
    t.stop();
    }
}

void reset(){
    printf("timer is reset\n");
    t.reset();
    t.stop();
    napp = false;
    state = false;
    tid = 60;
}

void add_5sec(){
    tid += 5;
    printf("Added 5 sec\n");
}

void minus_5sec(){
   tid -= 5;
    printf("Minus 5 sec\n");
}

int main()
{

DFRobot_RGBLCD lcd(16,2,D14,D15); lcd.init(); lcd.printf("Number: %i", 42); lcd.setRGB( 0, 0, 255);



    Butt1.rise(&start_stop);
    Butt2.rise(&reset);
    Butt3.rise(&add_5sec);
    Butt4.rise(&minus_5sec);
    while (true)
    {
        
        ned = tid - (duration_cast<seconds>(t.elapsed_time()).count());

        if (ned ==0) {
        t.stop(); 
        while(state == true){
        buzzer = on;
        thread_sleep_for(WAIT_TIME_MS2);
        buzzer = off;
        thread_sleep_for(WAIT_TIME_MS2);
        lcd.clear();
        
        lcd.printf(" Time: %i seconds ", ned);
       
        printf(" Time: %i seconds\n ", ned);
        if (state == !state){
            state = true;
            break;
        }
    }
        }
        
        
        lcd.clear();
        
        lcd.printf(" Time: %i seconds ", ned);
       
        printf(" Time: %i seconds\n ", ned);
        thread_sleep_for(WAIT_TIME_MS);
    }
   
        
}
