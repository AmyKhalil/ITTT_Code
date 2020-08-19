#include "Arduino.h"              //include de library 
#include "SoftwareSerial.h"       //include de library
#include "DFRobotDFPlayerMini.h"  //include de library

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;        // naam geven aan library 

int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
// ledjes assignen aan de bijbehorende pins
int LED1 = 13;
int LED2 = 12; 
// timer variabelen
unsigned long int then = millis(); // variabele voor de constante loop timer
unsigned long int timer = millis();

void setup()         //Alles wordt hier maar 1x gelezen 
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);                                     
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  
 if (!myDFPlayer.begin(mySoftwareSerial)) {                //Use softwareSerial to communicate with mp3.
    Serial.println(analogRead(sensorPin));                  //Een check voor als er een error is waardoor hij niet kan beginnen 
   
    Serial.println(F("Unable to begin:"));                  //Een check voor als er een error is waardoor hij niet kan beginnen 
    Serial.println(F("1.Please recheck the connection!"));  //Een check voor als er geen connectie is 
    Serial.println(F("2.Please insert the SD card!"));      //Een check voor als mijn SDKAart er niet in zit
    //while(true);                                            //de while loop omdat de loop altijd "true" is zal dus voor altijd doorgaan 
  }
  Serial.println(F("DFPlayer Mini connected.")); 
  Serial.println(sensorValue); //Hier kan je zien wanneer de dfplayer aangesloten is 
  myDFPlayer.setTimeOut(500);                               //Set serial communictaion time out 500ms 
  myDFPlayer.volume(30);  //Set volume value (0~30).        //Volume van de speaker 
}

void loop()                                                 
{ 
  // if loop die om de 15 seconden het rode ledje laat knipperen
  int duration = millis() - then;

  if (duration >= 15000) {
    then = millis;
    digitalWrite(LED2, HIGH); 
    delay(2000); 
    digitalWrite(LED2, LOW);    
  }
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  delay(100);
    // als iemand over de sensor gaat zet ledje aan en speel geluid af
    if(sensorValue>45){
      digitalWrite(LED1, HIGH); 
      delay(2000); 
      digitalWrite(LED1, LOW);
      if (millis() - timer > 3000) {
      timer = millis();
      myDFPlayer.next();
      //digitalWrite(LED2, LOW);
    }
  } 
}
