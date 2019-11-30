#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <ESP8266WebServer.h> 
#include <ESP8266mDNS.h> 
 
const char* ssid = "AndroidAP"; 
const char* password = "mcbv1466"; 
const int relayPin1=D0;
ESP8266WebServer server(80); 
/////////////////////////  Set-up  or Input and Output define/////////////////////
void setup() { 
pinMode(relayPin1, OUTPUT); 
Serial.begin(9600); 
connectToWiFi(); 
server.on("/", handleRoot);
server.begin();
Serial.println("HTTP server started");
} 
 
void loop() { 
server.handleClient();
} 
 
void connectToWiFi() { 
 
Serial.print("\n\nConnecting to "); 
Serial.println(ssid);  
WiFi.begin(ssid, password);  
while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
}  
Serial.println("\nWiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
} 
 
void handleRoot() {  
Serial.println("Got a Request");  
if (server.arg(0)[0] == '1') 
{
  digitalWrite(relayPin1, HIGH);
  } 
else if(server.arg(0)[0]=='0') 
{
  digitalWrite(relayPin1, LOW);
  }   
String msg = "";  
msg += "<html><head><style>h1,h2{text-align:center;color:blue;}body{background-color:white;}</style><body>\n"; 
msg += " <br><br><br><br><br><h1>InterFace to Control Relay Module</h1><br><br>";
msg += "<h2>Welcome</h2>";
msg += "<h1>Relay Remote</h1>";
msg += "<h2><a href='?a=1'/>Turn On device 1</a></h2>";
msg += "<h2><a href='?a=0'/>Turn Off device 1</a></h2>";
msg += "</body></html>";  
server.send(200, "text/html", msg);
}
