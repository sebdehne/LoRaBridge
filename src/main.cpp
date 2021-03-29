#include <Arduino.h>

void setup()
{
  // setup Serial
  Serial.begin(115200);
}

void loop()
{
  if (!Serial)
  {
    while (!Serial)
      ;

    // reset RN RN2483
    pinMode(8, OUTPUT);
    digitalWrite(8, LOW);
    delay(500);
    digitalWrite(8, HIGH);
    delay(100);

    Serial1.begin(57600);

    Serial.println("ready");
  }

  int i;
  if (Serial.available())
  {
    i = Serial.read();
    if (i >= 0)
    {
      Serial1.write(i);
    }
  }

  if (Serial1.available())
  {
    i = Serial1.read();
    if (i >= 0)
    {
      Serial.write(i);
    }
  }
}
