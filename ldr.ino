//Interfacing LDR Sensor using NodeMCU and sending data data to ThingSpeak
#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ThingSpeak.h>
String apiWritekey="MTJECKT9ONTPR552";
const char* ssid="ANSHUL";
const char* password="anshul123";
const char* server="api.thingspeak.com";

//Initialising the pins
int LDRpin = A0;
int intensity;
float res;
WiFiClient client;//creating an object of the class WiFiClient

void setup()
{
   pinMode(LDRpin,INPUT);
 
   Serial.begin(9600);
      delay(10);
       
 
       Serial.println("Connecting to : ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, password);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
   /*while(WiFi.status != WL_CONNECTED)
   {
       delay(100);
       Serial.print(".");
   }*/
   /*Serial.println("NodeMCU connected to WiFi: ");
   Serial.print(ssid);
   ThingSpeak.begin(client);*/
}


void loop()
{
     
     intensity=analogRead(LDRpin);
     res=intensity*(5.0/1023.0);
     //res=(10000*v0)/(3.3-v0);
     Serial.print(res);

     delay(1000);

     /*ThingSpeak.writeField(784092,1,intensity,apiWritekey);*/
     

     if (client.connect(server,80))
     {
      String postStr = apiWritekey;
      postStr+="&field1=";
      postStr+=String(res);
      postStr+="\r\n\r\n";


     /*client.print("GET https://api.thingspeak.com/update?api_key=MTJECKT9ONTPR552&field1=0\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
     Serial.print("Intensity : ");
     Serial.print(res);
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println();
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);*/

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(postStr.length());
       client.print("\n\n");
       client.print(postStr);
  
       Serial.print("Intensity: ");
       Serial.print(res);
       Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(10000);
}
