#include <ESP8266WiFi.h>
#include "Arduino.h"
#include <OneWire.h>
#include <time.h>
#include <Wire.h>

#define arduino_main_num 0

int sensor = 5; //D1
const char* myserver="18.223.29.244";
const char* MY_SSID="Seungchule의 iPhone";
const char* MY_PWD="qqqqqqqqqq";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectWifi();
  pinMode(sensor, INPUT); //인풋
  
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("************************");
  long state = digitalRead(sensor);
  
  Serial.print("connecting to ");
  Serial.println(myserver);
  WiFiClient client;
  const int httpPort=3000;

  if(!client.connect(myserver,httpPort)){
    Serial.println("connection failed");
    return;
  }

  String url="/main_send?isPerson=";

  String isPerson="";
  if(state == HIGH){
    Serial.println("Motion detected!");
    digitalWrite(16, HIGH);
    isPerson="1";
    
  } else {
    Serial.println("Motion absent!");
    digitalWrite(16, LOW);
    isPerson="0";
  }
  url+=isPerson+"&arduino_main_num="+String(arduino_main_num);

  Serial.print("Requesting URL:");
  Serial.println(url);
  client.print(String("GET ") + url+" HTTP/1.1\r\n"+"Host: "+myserver+"\r\n"+"Connection: close\r\n\r\n");
  while(client.available())
  {
    String line=client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  Serial.println("************************");

  
  delay(2000);
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
}//end connect
