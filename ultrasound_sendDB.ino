#include <ESP8266WiFi.h>
#include "Arduino.h"
#include <OneWire.h>
#include <time.h>
#include <Wire.h>

#define arduino_id "aaa"
int trigpinIN = 16; // D0
int echopinIN = 5; // D1
int trigpinOUT = 4; // D2
int echopinOUT = 0; // D3
int INflag = 0;
int prevINflag = 0;
int OUTflag = 0;
int prevOUTflag = 0;
int people = 0;
long durationIN, distanceIN, durationOUT, distanceOUT;
String url="";
String isPerson="";

const char* myserver="18.223.29.244";
const char* MY_SSID="Seungchule의 iPhone";
const char* MY_PWD="qqqqqqqqqq";
long calculate_distanceIN();
long calculate_distanceOUT();
void setup() {
  Serial.begin(9600);
  connectWifi();
  pinMode(trigpinIN, OUTPUT);
  pinMode(echopinIN, INPUT);
  pinMode(trigpinOUT, OUTPUT);
  pinMode(echopinOUT, INPUT);
}
void loop() {
  distanceIN = calculate_distanceIN();
  distanceOUT = calculate_distanceOUT();
  
  if(distanceIN <= 50)  INflag = 1;
  else  INflag = 0;

  if(INflag != prevINflag){
    while(INflag == 1){
      distanceOUT = calculate_distanceOUT();
      if(distanceOUT <= 50) OUTflag = 1;
      else  OUTflag = 0;
      
      if(OUTflag != prevOUTflag){
        if(OUTflag == 1){
          if(people != 0) // 0이 아닐 때
            people-=1;
          Serial.print("People absent in the home : ");
          Serial.println(people);
          if(people == 0) // 사람이 아예 없을때만 0값을 넘김
            isPerson="0";
          else
            isPerson="1";
          sendDB(); 
          while(1){
             Serial.println(calculate_distanceOUT());
             if(calculate_distanceOUT() > 50){
               OUTflag = 0; INflag = 0;
               break;
             }
             delay(200);
          }
          delay(500);
        }
        return;
      }
   }
  }  
  distanceOUT = calculate_distanceOUT();
  if(distanceOUT <= 50)  OUTflag = 1;
  else  OUTflag = 0;
  delay(100);
  if(OUTflag != prevOUTflag){
    while(OUTflag == 1){
      distanceIN = calculate_distanceIN();
      if(distanceIN <= 50) INflag = 1;
      else  INflag = 0;
      
      if(INflag != prevINflag){
        if(INflag == 1){
          people+=1;
          Serial.print("People detected in the home : ");
          Serial.println(people);
          isPerson="1";
          sendDB();
          while(1){
             Serial.println(calculate_distanceIN());
             if(calculate_distanceIN() > 50){
               OUTflag = 0; INflag = 0;
               break;
             }
             delay(200);
          }
          delay(500);
        }
        return;
      }
    }  
  }
}
void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}
long calculate_distanceIN()
{
  digitalWrite(trigpinIN, LOW); // Initialize
  delayMicroseconds(2); // add delay
  digitalWrite(trigpinIN, HIGH); // send ultrasound
  delayMicroseconds(10);
  digitalWrite(trigpinIN, LOW);
  durationIN = pulseIn(echopinIN, HIGH); // check time
  return ((340 * durationIN) / 10000) / 2;  // 안쪽 센서 거리 측정
}
long calculate_distanceOUT()
{
  digitalWrite(trigpinOUT, LOW); // Initialize
  delayMicroseconds(2); // add delay
  digitalWrite(trigpinOUT, HIGH); // send ultrasound
  delayMicroseconds(10);
  digitalWrite(trigpinOUT, LOW);
  durationOUT = pulseIn(echopinOUT, HIGH); // check time
  return ((340 * durationOUT) / 10000) / 2; // 바깥쪽 센서 거리 측정
}
void sendDB()
{
  url="";
  Serial.println("************************");
  Serial.print("connecting to ");
  Serial.println(myserver);
  WiFiClient client;
  const int httpPort=3000;
  if(!client.connect(myserver,httpPort)){
    Serial.println("connection failed");
    return;
  }
  url+="/main_send?isPerson="+isPerson+"&id=aaa"+"&people="+people;
  Serial.print("Requesting URL:");
  Serial.println(url);
  client.print(String("GET ") + url+" HTTP/1.1\r\n"+"Host: "+myserver+"\r\n"+"Connection: close\r\n\r\n");
  while(client.available())
  {
    String line=client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("************************");
}
