#include <Arduino.h>

bool trigger1 = false;
bool trigger2 = false;

unsigned long micros1 = 0;
unsigned long micros2 = 0;

long diff = 0;

void IRAM_ATTR triggered1()
{
  if (trigger1 == false)
  {
    trigger1 = true;
    micros1 = micros();
    detachInterrupt(12);
  }
}

void IRAM_ATTR triggered2()
{
  if (trigger2 == false)
  {
    trigger2 = true;
    micros2 = micros();
    detachInterrupt(13);
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  attachInterrupt(12, triggered1, FALLING);
  attachInterrupt(13, triggered2, FALLING);
}

void loop()
{

  if (trigger1 && trigger2)
  {
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.begin(9600);
    delay(20);
    Serial.print("Diff: ");
    diff = micros2 - micros1;
    Serial.print(diff);
    Serial.print(" = ");
    Serial.print(micros2);
    Serial.print(" - ");
    Serial.println(micros1);

    while (true)
    {
      Serial.print("Diff: ");
      diff = micros2 - micros1;
      Serial.print(diff);
      Serial.print(" = ");
      Serial.print(micros2);
      Serial.print(" - ");
      Serial.println(micros1);
    }
  }
}
