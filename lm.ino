int val;
int tempPin = A0;

void setup()
{
  pinMode(A0,INPUT);
 // Initialization of baud rate
Serial.print("Reading...");
Serial.println();
Serial.begin(115200);
}
void loop()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*3300; 
float cel = mv/10;
float farh = (cel*9)/5 + 32;

Serial.print("TEMPERATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);
 
Serial.print("TEMPERATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();
delay(1000);
}
