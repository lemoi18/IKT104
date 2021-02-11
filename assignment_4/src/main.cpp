#include <Arduino.h>
#include <Wire.h>
#include "DFRobot_RGBLCD.h"
#include <stm32l4xx_hal_iwdg.h>

IWDG_HandleTypeDef watchdog;

void begin();
void refresh();
#define I2C2_SCL    PB10
#define I2C2_SDA    PB11
const int colorR = 0;
const int colorG = 0;
const int colorB = 255;
DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show
TwoWire dev_i2c(I2C2_SDA, I2C2_SCL);

boolean running;
int last_millis;
long previousMillis = 0; 
int c = 0;
int long time_left = 100000000000;
int long time_orginal =100000000000;
int long time_continue = 0;
volatile byte go;



void setup() {
  // put your setup code here, to run once:
  dev_i2c.begin();
  lcd.init();
  lcd.setRGB(colorR, colorG, colorB);
  pinMode(D10, INPUT_PULLUP);
  pinMode(D11, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

   watchdog.Instance = IWDG;
    watchdog.Init.Prescaler = IWDG_PRESCALER_256;
    watchdog.Init.Reload = 1240;   // 32 000 / 256 = 125 per second, thus 250 = 2 seconds
    watchdog.Init.Window = 0xFFF; // Disable window mode

    HAL_IWDG_Init(&watchdog);


 
  delay(1);
  attachInterrupt(D11,  begin,  CHANGE);
  attachInterrupt(D10 , refresh, CHANGE);

  last_millis = millis();
  running = true;
 
}

volatile byte state = LOW;

void loop() {
 
lcd.display();
 
    // print the number of seconds since reset:
    lcd.clear();

  if(running){
 time_left -= ( millis() - last_millis );

  } else {
    HAL_IWDG_Refresh(&watchdog);
  }
  last_millis = millis();
  float(time_continue) = float((time_orginal)/1000) - float((time_left)/1000);
  lcd.print((float((time_orginal)/float(1000)) - float((time_left)/float(1000))));
  if(time_left < 0 ){
 
    time_left = int(random(60000));
  }
}
void begin()
{ 
running = !running;
 

}

void refresh(){

  HAL_IWDG_Refresh(&watchdog);
}