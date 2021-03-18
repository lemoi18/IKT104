/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
 
#include "mbed.h"
#include <cstdio>
 
struct Variable{
Mutex mutex;
int min;
int sec;
 
}vara;
 
 
 
void thread_min(struct Variable *abc)
{
 
    while (true) {
        abc->mutex.lock();
        if(abc->sec == (abc->min + 1)*60)
        {
            abc->min += 1;
        }
         abc->mutex.unlock();
        ThisThread::sleep_for(1000ms);
 
    }
}
void thread_sec(struct Variable *abc)
{
    while (true) {
        abc->mutex.lock();
        abc->sec += 1;
        abc->mutex.unlock();
        ThisThread::sleep_for(1000ms);
 
    }
}
 
void thread_clock(struct Variable *abc)
{
    while (true) {
        abc->mutex.lock();
        printf("the clock in minuts is %d, and in seconds is %d\n", abc->min, abc->sec);
        abc->mutex.unlock();
        ThisThread::sleep_for(500ms);
 
    }
}
 
int main()
{
    Variable abc;
    abc.min = 0;
    abc.sec = 0;
    Thread thread1;
    Thread thread2;
    Thread thread3;
 
    thread1.start(callback(thread_min, &abc));
    thread2.start(callback(thread_sec, &abc));
    thread3.start(callback(thread_clock, &abc));
 
    thread1.set_priority(osPriorityHigh);
    thread2.set_priority(osPriorityHigh);
    thread3.set_priority(osPriorityNormal);
 
    while (true) {
 
        ThisThread::sleep_for(500ms);
    }
}