int trigPin = 10;
int echoPin = 13;

float duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  //Write a pulse to the HC-SR04 Trigger Pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Measure the response time
  duration = pulseIn(echoPin, HIGH);

  //Determine distance
  distance = (duration / 2) * 0.0343;

  //Send results to serial monitor
  Serial.print("\nDistance = ");
  if (distance >= 400 || distance <= 2) {
    Serial.print("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.print(" cm");
  }


}
