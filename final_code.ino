int motorL = 12;
int motorR = 10;

int coilL = A0;
int coilR = A2;

int baseSpeed = 140;     // forward speed
float Kp = 0.7;          // steering strength
int tolerance = 150;      // ignore small noise

void setup() {
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  int left = analogRead(coilL);
  int right = analogRead(coilR);

  int error = left - right;

  // ignore tiny differences
  if (abs(error) < tolerance) {
    error = 0;
  }

  int correction = Kp * error;

  int speedL = baseSpeed - correction;
  int speedR = baseSpeed + correction;

  speedL = constrain(speedL, 0, 255);
  speedR = constrain(speedR, 0, 255);

  analogWrite(motorL, speedL);
  analogWrite(motorR, speedR);

  // debugging
  Serial.print("L:");
  Serial.print(left);
  Serial.print(" R:");
  Serial.print(right);
  Serial.print(" E:");
  Serial.print(error);
  Serial.print(" SL:");
  Serial.print(speedL);
  Serial.print(" SR:");
  Serial.println(speedR);

  delay(10);
}
