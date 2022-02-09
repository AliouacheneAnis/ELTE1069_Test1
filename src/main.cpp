/*
  Titre      : Clapet 
  Auteur     : Anis Aliouachene
  Date       : 09/02/2022
  Description: controle servo moteur a l'aide d'un capteur de rotation 
  Version    : 0.0.1
*/


#include <Arduino.h>
#include<Servo.h>
#include <WIFIConnector_MKR1010.h>
#include<MQTTConnector.h>

// Declaration constantes 

const int ROTATION_SENSOR_PIN = A1 ;
const int SERVO_PIN = 9; 

// Declaration Variables 
int ValeurRotation; 
int pos = 0, Lastpos = 0, LastValeur; 

// objet moteur 
Servo myservo;

void setup() {
  
  // Setup des broches et connexion WIfi MQTT
  Serial.begin(9600); 

  wifiConnect(); 
  MQTTConnect();

  pinMode(ROTATION_SENSOR_PIN, INPUT);
  myservo.attach(SERVO_PIN);

}

void loop() {
  
  // Capture donnees sur le capture de rotation analogue 
  ValeurRotation = analogRead(ROTATION_SENSOR_PIN); 

  // Transformation a l'aide de la fonction map
  pos = map(ValeurRotation, 0, 1023, 0, 90);
  
  // Si y a un changement de valeur 
    if( Lastpos != pos || LastValeur != ValeurRotation ){
      myservo.write(pos); 
      Lastpos = pos; 
      LastValeur = ValeurRotation; 
      appendPayload("Valeur rotation ", ValeurRotation);
      appendPayload("Position ", pos); 
      sendPayload();
    }

}