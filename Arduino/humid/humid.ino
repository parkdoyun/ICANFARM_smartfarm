
#include <SoftwareSerial.h>

bool flag = false;
float now_string = 0;

int sensor = 0;
int motor = 9;

int R_max = 1023;
int R_min = 0;
int R_current = 500;
int difference = R_max - R_current;

unsigned long past =0;
unsigned long pasttime =0;

void setup()
{
  Serial.begin(115200);
  pinMode(motor, OUTPUT);
  pasttime = millis();
  digitalWrite(motor, LOW);
  Serial.flush();
}

void loop()
{
  sensor = analogRead(A0);
  float now_sensing = (float)(1023-sensor)/1023*100;

  if(Serial.available()){
    if(!flag){
      Serial.readString();
      flag = true;
      digitalWrite(motor, HIGH);
      past = millis();
    }
  }

  if(millis() - past >= 5000){
    if(flag){
      digitalWrite(motor, LOW);
      flag = false;
    }
  }

  if(millis() - pasttime >= 10000){
    String str = "@";
    str += String(now_sensing, 1);
    str += "#";
    Serial.flush();
    Serial.print(str);
    pasttime = millis();
  }
}
