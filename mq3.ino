 #include<ESP8266WiFi.h>
#include<WiFiClient.h>
  
  float sensorVoltage; 
  float sensorValue;

String apiWritekey="5EKEGDB7PQZD6H16";
const char* ssid="AndroidAP";
const char* password="mcbv1466";
const char* server="api.thingspeak.com";
WiFiClient client;



void setup() 
{
  Serial.begin(9600);
 WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid,password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Nodemcu connected to WiFi");
  Serial.println(ssid);
  Serial.println();
  

}
 
void loop() 
{

 
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*5.0;
  Serial.print("\n");
  Serial.print("Reading = ");
  Serial.print(sensorVoltage);
  Serial.println();

  delay(1000);

   if (client.connect(server,80)){
  String tsData = apiWritekey;
  tsData+="&field1=";
  tsData+=String(sensorVoltage);
  tsData+="\r\n\r\n";


     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
    
     //Serial.print(sensorVoltage);
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);
}
