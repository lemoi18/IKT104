#include <Wire.h>
#include "DFRobot_RGBLCD.h"
#include <Arduino.h>
#include <HTS221Sensor.h>
#define I2C2_SCL    PB10
#define I2C2_SDA    PB11
 
// I2C
TwoWire dev_i2c(I2C2_SDA, I2C2_SCL);
 
// Components.
HTS221Sensor  HumTemp(&dev_i2c);
 
DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show
 
 int colorR = 255;
 int colorG = 0;
 int colorB = 0;
int x = 0;
int oldButtonState = LOW;
int buttonPin = 1;
int current_state = 0;
 
void setup() {
    // initialize
    Serial.begin(9600);
    lcd.init();
    pinMode(buttonPin, INPUT_PULLUP);
    lcd.setRGB(colorR, colorG, colorB);
     // Initialize I2C bus.
  dev_i2c.begin();
 
  // Initlialize components.
  HumTemp.begin();
  HumTemp.Enable();
    
 
}
 
void loop() {
  delay(100);
 
  float humidity, temperature;
   // Get the current state of the button
  int newButtonState = digitalRead(buttonPin);
  Serial.println(newButtonState);
  // Has the button gone high since we last read it?
  
 
 
 
        while (1)
        {
 
 
 
 
 
 
 
 
          lcd.clear();
 
          HumTemp.GetTemperature(&temperature);
          if (temperature < 20 )
            {
          colorR = 0, colorB = 255, colorG = 0;
 
          lcd.setRGB(colorR, colorG, colorB);
          }
          if ( temperature >= 20  || temperature <= 24  )
          {
          colorR = 255, colorB = 0, colorG = 165;
 
         lcd.setRGB(colorR, colorG, colorB);
          }
 
          if (temperature >= 24 )
          {
          colorR = 255, colorB = 0, colorG =0;
 
          lcd.setRGB(colorR, colorG, colorB);
          }
  
          lcd.write("Temp[C]: ");
          lcd.print(temperature);
          Serial.print("Temp[C]: ");
           Serial.println(temperature, 2);
 
          if(digitalRead(buttonPin)==1){
            x=1;
            break;}
 
 
          delay(100);
 
        }
 
 
   
      // Toggle off
      
      int redish = 0;
      int greenish = 0;

      while(1){
 
      delay(100);
       lcd.clear();
      HumTemp.GetHumidity(&humidity);
      
      
      redish = map(humidity,100, 0, 255 ,0);
      greenish = map(humidity,100, 0, 255 ,0);

      lcd.setRGB(redish, greenish, 255);
 
 
 
 
      lcd.write("Hum[%]: ");
      lcd.print(humidity);
       Serial.print("\nHum[%]: ");
        Serial.print(humidity, 2);
     
 
      if(digitalRead(buttonPin)==1){
            x=0;
            break;
          }
          
      }
    
  
  // Store the button's state so we can tell if it's changed next time round
 
}