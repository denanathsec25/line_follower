#define ENA PA8
#define IN1 PB1
#define IN2 PB0

#define ENB PA9
#define IN3 PB5   // Fixed from PB0
#define IN4 PB6   // Fixed from PB1

#define STBY PB12

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  // Run both motors forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void loop() {
  // Nothing needed - motors run from setup()
}