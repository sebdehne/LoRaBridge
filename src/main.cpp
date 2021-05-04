#include <Arduino.h>

void resetRN2483();

const unsigned long LEDdelayInMs = 250;
unsigned long ledSwitchedAt = 0;
bool rxOrTx = true;
void handleLED();

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial1.begin(57600);

  handleLED();
}

void loop()
{
  int i;
  while (Serial.available())
  {
    i = Serial.read();
    if (i < 0)
      break;

    rxOrTx = true;

    if (i == '!')
    {
      resetRN2483();
      break;
    }

    Serial1.write(i);
  }

  while (Serial1.available())
  {
    i = Serial1.read();
    if (i < 0)
      break;

    rxOrTx = true;

    Serial.write(i);
  }

  handleLED();
}

void resetRN2483()
{
  // reset RN RN2483
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(500);
  digitalWrite(2, HIGH);
  delay(100);
}

void handleLED()
{
  unsigned long now = millis();
  if (now - ledSwitchedAt < LEDdelayInMs)
  {
    return;
  }

  if (digitalRead(LED_BUILTIN))
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (rxOrTx)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  rxOrTx = false;
  ledSwitchedAt = now;
}