
#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

bool flag = false;
float now_sensing =0;

int motor = 9;

unsigned long past = 0;
unsigned long pasttime =0;

void setup()
{
  Serial.begin(115200);
  pinMode(motor, OUTPUT);
  dht.begin();
  pasttime = millis();
  digitalWrite(motor, HIGH);
}

void loop()
{
  float temperature = dht.readTemperature();
  if(!isnan(temperature)){
    now_sensing = temperature;
  }

  if(Serial.available()){
    if(!flag){
      Serial.readString();
      flag = true;
      digitalWrite(motor, LOW);
      past = millis();
    }
  }

  if(millis() - past >= 5000){
    if(flag){
      Serial.println("sop");
      digitalWrite(motor, HIGH);
      flag = false;
    }
  }

  if(millis() - pasttime >= 10000){
    String srt = "@";
    srt += String(temperature, 1);
    srt += "#";
    Serial.flush();
    Serial.print(srt);
    pasttime = millis();
  }
}
