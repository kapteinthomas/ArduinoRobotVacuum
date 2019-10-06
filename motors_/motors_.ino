int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

void setup() {
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
}

void loop() {
  delay(1000);
  forward();
  delay(1000);
  halt();
  delay(1000);
  backward();
  delay(1000);
  halt();
  delay(1000);
  turn_right();
  turn_left();
}

void forward() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 150);  
  analogWrite(pwm_b, 150);
}

void backward() {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, LOW); 

  analogWrite(pwm_a, 150);  
  analogWrite(pwm_b, 150);
  
}

void halt() {
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
}

void turn_left() {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 150);  
  analogWrite(pwm_b, 150);

  delay(500);
}

void turn_right() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, LOW);

  analogWrite(pwm_a, 150);  
  analogWrite(pwm_b, 150);

  delay(500);
}
