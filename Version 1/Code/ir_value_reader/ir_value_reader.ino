// ===== 5 IR SENSOR ANALOG ARRAY TEST CODE FOR STM32F103 =====

// Analog pins on STM32
int sensors[5] = {PA0, PA1, PA2, PA3, PA4};  
int values[5];                               

void setup()
{
  Serial.begin(9600);   // USB serial
}

void loop()
{
  // Read all 5 sensors
  for(int i = 0; i < 5; i++)
  {
    values[i] = analogRead(sensors[i]);
  }

  // Print sensor values
  for(int i = 0; i < 5; i++)
  {
    Serial.print(values[i]);
    Serial.print("   ");
  }

  Serial.println();

  delay(200);
}