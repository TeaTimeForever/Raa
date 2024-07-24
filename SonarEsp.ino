#include "connect_wifi.h"
#include "make_request.h"

const int trigPin = 12;
const int echoPin = 14;
const int buttonPin = 13;
const int jumpIndicationLedPin = 4;

int buttonState = 0;

String serverAPI = "https://255510aa-944a-47ac-9de8-bbe81703253c.mock.pstmn.io/register";

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float baseDistance = 4;

String response;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(jumpIndicationLedPin, OUTPUT);

  digitalWrite(buttonPin, LOW);
  connect_to_wifi();
}

void loop() {
  analogWrite(buttonPin, LOW);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY/2;
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    Serial.print("+");
    baseDistance = distanceCm - 3 ;
    Serial.print("Base Distance (cm): ");
    Serial.println(baseDistance);
  }

  if(distanceCm < baseDistance) {
    digitalWrite(jumpIndicationLedPin, HIGH);
    Serial.println("Doggy jumps!!");
    digitalWrite(jumpIndicationLedPin, LOW);
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("-");
      response = getRequest(serverAPI);
      Serial.println(response);
      delay(3000);
    } else {
      Serial.println("DISCONNECTED");
    }
  }




  delay(50);
}