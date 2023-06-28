#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 2        // DHT11 센서의 데이터 핀을 아두이노의 2번 핀에 연결
#define DHTTYPE DHT11   // DHT11 센서를 사용

DHT dht(DHTPIN, DHTTYPE);

bool flag = false;    // 현재 작동상태 기록
float now_sensing = 0;        // 현재 센싱값

int motor = 9;        // 릴레이모듈 : 팬 모터

int past = 0;       //  모터 작동을 위한 시간 기록
int pasttime = 0;   // 10분마다의 전송을 위한 시간 기록 


// 모터 on
void run_motor()
{
  Serial.print(" motor start!! ");
  digitalWrite(motor, HIGH); 
}

// 모터 off
void stop_motor()
{
  Serial.print(" motor stop!! ");
  digitalWrite(motor, LOW);
}

// 송신함수 
void SendMessage()
{
  Serial.print(" SendMessage : ");
}
 
void setup()
{
  Serial.begin(9600);
  pinMode(motor,OUTPUT);      // 모터핀설정
  dht.begin();
  pasttime = millis();
}
 
void loop()
{
  float temperature = dht.readTemperature();
  
  // 온도 값이 유효한지 확인
  if (!isnan(temperature)) {
    now_sensing = temperature;
    // // 시리얼 모니터에 온도 값 출력
    // Serial.print("Temperature: ");
    // Serial.print(now_sensing);
    // Serial.println("°C");
    // delay(1000);
  }

  run_motor();
  delay(5000);
  stop_motor();
  delay(5000);

  
}
