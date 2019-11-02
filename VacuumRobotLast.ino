
int trigPin = 10;
int echoPin = 13;

int buttonPin = 4;
int buttonDelay = 500;

int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4

int speedFA = 150;
int speedFB = 150;

int speedBA;
int speedBB;
int turn;

int vacuumPin = 3;

float duration, distance;

bool on = false;
bool colliding = false;

void setup() {
  Serial.begin(9600);
  // Set up pins for button and vaccuum motor
  pinMode(buttonPin, INPUT);
  pinMode(vacuumPin, OUTPUT);

  // Set up pins for motors
  pinMode(pwm_a, OUTPUT); // Determines speed
  pinMode(pwm_b, OUTPUT); // Determines speed
  pinMode(dir_a, OUTPUT); // Determines direction
  pinMode(dir_b, OUTPUT); // Determines direction

  // Set up pins for echo
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (on) {
    // Pump on
    digitalWrite(vacuumPin, HIGH);
    distance = get_distance();
    
    if (distance < 10 && colliding != true) {
      // First time collision
      colliding = true;
      speedBA = random(20, 150);
      speedBB = random(20, 150);
      turn = 0;
    }
    else if (distance < 50 && colliding == true) {
      // Still backing up
      backUp(speedBA, speedBB, turn);
      Serial.println(speedBA);
      Serial.println(speedBB);
    }
    else if (distance >= 50 && colliding == true) {
      //backed up enough
      colliding = false;
      turn = random(1, 3);
      backUp(speedBA, speedBB, turn);
      delay(1000);
      
    }
    else {
      Serial.println("Forward");
      forward(speedFA, speedFB);
    }
    
  }
  else {
    stopMotors();
    //Turn Vacuum off
    digitalWrite(vacuumPin, LOW);
  }

  
  //Toggle button on or off
  if (digitalRead(buttonPin) == HIGH && on == false) {
    on = true;
    delay(buttonDelay);
  }
  else if (digitalRead(buttonPin) == HIGH && on == true) {
    on = false;
    delay(buttonDelay);
  }
}

float get_distance() {
  //Write pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Measure the response time
  duration = pulseIn(echoPin, HIGH);

  //Calculate and return distance
  return (duration / 2) * 0.0343;
}

void forward(int A, int B) {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, A);  
  analogWrite(pwm_b, B);
}

void stopMotors() {
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
}


void backUp(int A, int B, int turn) {
  if (turn == 0) {
    digitalWrite(dir_a, LOW); 
    digitalWrite(dir_b, LOW);
  }
  else if (turn == 1) {
    digitalWrite(dir_a, HIGH); 
    digitalWrite(dir_b, LOW);
  }
  else {
    digitalWrite(dir_a, LOW); 
    digitalWrite(dir_b, HIGH);
  }
  analogWrite(pwm_a, A);  
  analogWrite(pwm_b, B);
}
/*
void backUpAndTurn() {
  Serial.println("Backing up");
  stopMotors();
  delay(1000);

  // Generate 0 or 1, to dertimen which direction to turn in
  bool choice = random(0, 2);
  if (choice == 1) {
    digitalWrite(dir_a, HIGH); 
    digitalWrite(dir_b, LOW);
  }
  else {
    digitalWrite(dir_a, HIGH); 
    digitalWrite(dir_b, LOW);
  }

  // Back up in random direction
  int randomIntA = random(100, 150);
  int randomIntB = random(100, 150);
  analogWrite(pwm_a, randomIntA);  
  analogWrite(pwm_b, randomIntB);
  delay(3000);

  // Finally set colliding to false
  colliding = false;
  Serial.println("Done backing up");
} */
