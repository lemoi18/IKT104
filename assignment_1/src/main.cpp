#include <Arduino.h>


void setup()
{
  
    Serial.begin(9600);
    Serial.print("setup");
    pinMode(D13, OUTPUT);
    Serial.println("Input 1 to Turn LED on and 2 to off\n");
}
int x = 1; //start with the light being ON


void loop()
{
    x = Serial.read();
    if(x == '0')
    {
    digitalWrite(D13, LOW);
    Serial.print("You flicked the light OFF\n");
    // Serial.println("off");
    delay(1000);
    }
    else if(x == '1')
    {
    digitalWrite(D13, HIGH);
    // Serial.println("on");
    Serial.print("You flicked the light ON\n");
    delay(1000);
  }
}