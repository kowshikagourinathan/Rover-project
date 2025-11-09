#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define trigPin 4
#define echoPin 5
#define motorLeft1 12
#define motorLeft2 13
#define motorRight1 14
#define motorRight2 15

HardwareSerial sim7600(1);
TinyGPSPlus gps;

long duration;
int distance;
String serverURL = "http://192.168.1.10:8000/update"; // Replace with your API endpoint

void setup() {
  Serial.begin(115200);
  sim7600.begin(115200, SERIAL_8N1, 16, 17);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);
  Serial.println("Smart_Rover initialized.");
}

void loop() {
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 20) {
    stopMotors();
    Serial.println("Obstacle detected!");
  } else {
    moveForward();
  }
  sendDataToServer(distance);
  delay(2000);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void moveForward() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
}

void stopMotors() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
}

void sendDataToServer(int dist) {
  HTTPClient http;
  String data = "{"distance": " + String(dist) + "}";
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(data);
  Serial.println(httpCode);
  http.end();
}
