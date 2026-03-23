#define S5 PA0
#define S4 PA1
#define S3 PA2
#define S2 PA3
#define S1 PA4

void setup() 
{
  Serial.begin(9600);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
}

void loop() 
{
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  Serial.print("S1: "); Serial.print(s1);
  Serial.print("  S2: "); Serial.print(s2);
  Serial.print("  S3: "); Serial.print(s3);
  Serial.print("  S4: "); Serial.print(s4);
  Serial.print("  S5: "); Serial.println(s5);

  delay(500);
}