#define S1 PA4  // Far Left
#define S2 PA3  // Left
#define S3 PA2  // Center
#define S4 PA1  // Right
#define S5 PA0  // Far Right

#define ENA  PA8
#define IN1  PB1
#define IN2  PB0

#define ENB  PA9
#define IN3  PB5
#define IN4  PB6

#define STBY PB12

// ✅ Calibrated motor speeds
int leftSpeed  = 205;
int rightSpeed = 205;
int leftTurn   = 105;
int rightTurn  = 105;
int lastError  = 0;

// ✅ Forward declarations
void forward();
void turnLeft();
void hardLeft();
void turnRight();
void hardRight();
void stopMotors();

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(ENA,  OUTPUT);
  pinMode(IN1,  OUTPUT);
  pinMode(IN2,  OUTPUT);

  pinMode(ENB,  OUTPUT);
  pinMode(IN3,  OUTPUT);
  pinMode(IN4,  OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  delay(2000);
}

void loop() {
  // ✅ BLACK LINE — sensor reads LOW on line (same as original black=1)
  int s1 = !digitalRead(S1);  // Far Left
  int s2 = !digitalRead(S2);  // Left
  int s3 = !digitalRead(S3);  // Center
  int s4 = !digitalRead(S4);  // Right
  int s5 = !digitalRead(S5);  // Far Right

  // =============================================
  //              FORWARD
  // s4+s5 center = original s4+s5 center
  // =============================================
  if (
    (!s1 && !s2 && s3  && !s4 && !s5) ||  // Center only
    (!s1 && !s2 && s3  &&  s4 && !s5) ||  // Center + slight right
    (!s1 &&  s2 && s3  &&  s4 && !s5) ||  // Center + both sides
    (!s1 &&  s2 && s3  &&  s4 &&  s5) ||  // Center + right heavy
    ( s1 &&  s2 && s3  &&  s4 &&  s5)     // All sensors — intersection
  ) {
    lastError = 0;
    forward();
  }

  // =============================================
  //              RIGHT TURNS
  // Line is shifting to the right
  // =============================================
  else if (
    (!s1 && !s2 && !s3 &&  s4 && !s5) ||  // Slight right
    (!s1 && !s2 &&  s3 &&  s4 &&  s5) ||  // Center + far right
    (!s1 && !s2 && !s3 &&  s4 &&  s5)     // Right + far right
  ) {
    lastError = 1;
    turnRight();
  }

  else if (
    (!s1 && !s2 && !s3 && !s4 &&  s5)     // Far right only — hard right
  ) {
    lastError = 2;
    hardRight();
  }

  // =============================================
  //              LEFT TURNS
  // Line is shifting to the left
  // =============================================
  else if (
    (!s1 &&  s2 && !s3 && !s4 && !s5) ||  // Slight left
    ( s1 &&  s2 &&  s3 && !s4 && !s5) ||  // Center + far left
    ( s1 &&  s2 && !s3 && !s4 && !s5)     // Left + far left
  ) {
    lastError = -1;
    turnLeft();
  }

  else if (
    ( s1 && !s2 && !s3 && !s4 && !s5)     // Far left only — hard left
  ) {
    lastError = -2;
    hardLeft();
  }

  // =============================================
  //         LINE LOST — use last known direction
  // =============================================
  else if (!s1 && !s2 && !s3 && !s4 && !s5) {
    if      (lastError < 0) hardLeft();
    else if (lastError > 0) hardRight();
    else                    stopMotors();
  }

  // ✅ Default
  else  {
    forward();
  }
}

// ---------------- MOTOR FUNCTIONS ----------------

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftSpeed);   // 205-left forward
  analogWrite(ENB, rightSpeed);  // 205-right forward
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftTurn);   
  analogWrite(ENB, rightSpeed);  
}

void hardLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);           // Left stop
  analogWrite(ENB, rightSpeed);  // 205 — Right forward
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftSpeed);   // 205 — Left fast
  analogWrite(ENB, rightTurn);   // 75  — Right slow
}

void hardRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftSpeed);   // 205 — Left forward
  analogWrite(ENB, 0);           // Right stop
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}