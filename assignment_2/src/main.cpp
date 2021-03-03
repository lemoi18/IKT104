#include <Arduino.h>
 
int LED_1 = D5;
int LED_2 = D9;
int LED_3 = D10;
int potentiometer = A1;
 
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D5, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, INPUT_PULLUP);
}
 
void loop() {
  int x = analogRead(A1); // Potentiometer
  int y = digitalRead(D12); // Button
  int a = (x - 341); // a is value between 33% and 66%
  int b = (x - (341*2)); // b is value between 66% and 100%
 
  delay(100); // Delays potentionmeter input to 10 times a second.
  Serial.println(x);
 
 
if(digitalRead(D11) == 1)
  {
    analogWrite(LED_1, 1023);
    analogWrite(LED_2, 1023);
    analogWrite(LED_3, 1023);
  }
  else if(digitalRead(D11) == 0)
  {
 
  if( x > 0 && x <= 341)
  {
  analogWrite(LED_1, x);
  analogWrite(LED_2, 0);
  analogWrite(LED_3, 0);
 
 
  }
 
  if(x >=341 && x <= 682)
  {
  analogWrite(LED_2, a);
  analogWrite(LED_1, 1023);
  analogWrite(LED_3, 0);
  }
 
  if(x >= 682 && x <= 1023)
  {
  analogWrite(LED_3, b);
  analogWrite(LED_1, 1023);
  analogWrite(LED_2, 1023);
  }
 
  }
}