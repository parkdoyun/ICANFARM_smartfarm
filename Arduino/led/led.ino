#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

const int pin7 = 7;
const int pin8 = 8;
bool flag = false;

unsigned long pasttime =0;

void setup()
{
  Serial.begin(115200);
  if(!sgp.begin()){
    Serial.println("ERROR");
    while(1);
  }
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, LOW);

  pasttime = millis();
}

void loop()
{
  if(Serial.available()){
    String x = Serial.readString();
    if(x == "1"){
      if(!flag){
        flag = true;
        digitalWrite(pin7, HIGH);
        digitalWrite(pin8, HIGH);
      }
    }
    else{
      if(flag){
        flag = false;
        digitalWrite(pin7, LOW);
        digitalWrite(pin8, LOW);
      }
    }
  }

  if(!sgp.IAQmeasure()){
    return;
  }

  if(millis() - pasttime >= 10000){
    String str = "@";
    str += String(sgp.eCO2);
    str += "#";
    Serial.flush();
          Serial.print(str);
    pasttime = millis();
  }
}
