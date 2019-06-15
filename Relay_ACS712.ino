#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Arduino.h"
#include <OneWire.h>
#include <time.h>
#include <Wire.h>
#include "ESP8266HTTPClient.h"
#define arduino_id "aaa"
#define arduino_sub_num 1
int relay_pin = 2;  // D4 Initialized the pin for relay module
long interval=15;
long max_interval=20;
long time_count=0;
const char* myserver="18.223.29.244";
const char* MY_SSID="Seungchule의 iPhone";
const char* MY_PWD="qqqqqqqqqq";

int send_count=0;

float getVPP();
const int sensorIn = A0;
int mVperAmp = 185; // use 185 for 5A Module and 100 for 20A Module

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
int getisPerson()
{
  
  WiFiClient client;
  String response_url="/sub/response?id=";
  response_url+=arduino_id;


  String str1="";
// client.print(String("GET ") + url+" HTTP/1.1\r\n"+"Host: "+myserver+"\r\n"+"Connection: close\r\n\r\n");
  const int httpPort=3000;
  if(!client.connect(myserver,httpPort)){
    Serial.println("connection failed");
    return -1;
  }
  client.print(String("GET ")+response_url+" HTTP/1.1\r\n" + "Host: "+myserver+"\r\n"+"Connection:close\r\n\r\n");

  while (client.available() == 0) {
      String line = client.readString();
      int index=line.indexOf("person");
      int len=line.length();
      str1=line.substring(index,len);

    //  Serial.println(line);
      if(str1=="person=1")
     {
        return 1;
     }
     else{
       return 0;
     }
  }
  
}
void setup(){
  Serial.begin(9600);
  //connectWifi();
  pinMode(relay_pin, OUTPUT);   // Declared relay module pin as Output pin
  // Make the relay module initial state as low, Relay works opposite
  digitalWrite(relay_pin, HIGH);
}
void loop(){
  WiFiClient client;


  int isPerson=getisPerson();

  if(isPerson==-1)
  {
    Serial.println("No Connection!");
    return;
  }
  const int httpPort=3000;
  if(!client.connect(myserver,httpPort)){
    Serial.println("connection failed");
    return;
  }

  
  if(isPerson == 0){
    digitalWrite(relay_pin, HIGH);
  }
  else if(isPerson == 1){
    digitalWrite(relay_pin, LOW);
  }


       
  Voltage = getVPP();
   VRMS = (Voltage) *100; 
  //VRMS = (Voltage/2.0) *0.707; 
  AmpsRMS = (VRMS*100)/mVperAmp;
  //AmpsRMS = (Voltage * 1000)/mVperAmp;
  float Power;

  Serial.print(Voltage);
  Serial.println(" Voltage");
  Serial.print(VRMS);
  Serial.println(" Voltage RMS");
  Serial.print(AmpsRMS);
  Serial.println(" Amps RMS");
  Power=VRMS*AmpsRMS*0.707*0.85;
  Serial.println(Power);

  send_count+=1;
  
  if(Power<500 && Power>4){
    String url="/sub/send?id=";
    url+=arduino_id;
    url+="&arduino_sub_num=";
    url+=String(arduino_sub_num);
    url+="&power=";
    url+=String(Power);
  
    Serial.print("Requesting URL:");
    Serial.println(url);
    client.print(String("GET ") + url+" HTTP/1.1\r\n"+"Host: "+myserver+"\r\n"+"Connection: close\r\n\r\n");
    while(client.available())
    {
      String line=client.readStringUntil('\r');
  //    Serial.print(line);
    }
  }
  else
  {
    String url="/sub/send?id=";
    url+=arduino_id;
    url+="&arduino_sub_num=";
    url+=String(arduino_sub_num);
    url+="&power=";
    url+=String(0);
  
    Serial.print("Requesting URL:");
    Serial.println(url);
    client.print(String("GET ") + url+" HTTP/1.1\r\n"+"Host: "+myserver+"\r\n"+"Connection: close\r\n\r\n");
    while(client.available())
    {
      String line=client.readStringUntil('\r');
  //    Serial.print(line);
    }
  }

  for(int j=0;j<60;j++)
  {
    delay(1000);
  }
  
 // Serial.println();
 // Serial.println("closing connection");
  //Serial.println("************************");
  
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
float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000)
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
 
