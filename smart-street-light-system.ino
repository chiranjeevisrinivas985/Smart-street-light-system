#include <Adafruit_LiquidCrystal.h>

// ---------------- LCD ----------------
Adafruit_LiquidCrystal lcd(0);

// ---------------- Pin Assignments ----------------
const int ldrPin = A0;

// IR Sensors
const int irPin1 = 8;
const int irPin2 = 9;
const int irPin3 = 10;
const int irPin4 = 11;
const int irPin5 = 12;
const int irPin6 = 13;

// LEDs
const int ledPin1 = 7;
const int ledPin2 = 6;
const int ledPin3 = 5;
const int ledPin4 = 4;
const int ledPin5 = 3;
const int ledPin6 = 2;

// LDR threshold
const int ldrThreshold = 550;

// ---------------- Variables ----------------
int ldrValue;

int irState1;
int irState2;
int irState3;
int irState4;
int irState5;
int irState6;


// ---------------- Setup ----------------
void setup()
{
  // IR sensor pins
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(irPin3, INPUT);
  pinMode(irPin4, INPUT);
  pinMode(irPin5, INPUT);
  pinMode(irPin6, INPUT);

  // LED pins
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);

  // LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Serial Monitor
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("SMART STREET");
  lcd.setCursor(0, 1);
  lcd.print("LIGHT SYSTEM");

  delay(2000);
  lcd.clear();
}


// ---------------- Main Loop ----------------
void loop()
{
  // Read LDR
  ldrValue = analogRead(ldrPin);

  // Read IR sensors
  irState1 = digitalRead(irPin1);
  irState2 = digitalRead(irPin2);
  irState3 = digitalRead(irPin3);
  irState4 = digitalRead(irPin4);
  irState5 = digitalRead(irPin5);
  irState6 = digitalRead(irPin6);

  // Display LDR value on Serial Monitor
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);


  // ==================================================
  // NIGHT / LOW LIGHT CONDITION
  // ==================================================

  if (ldrValue < ldrThreshold)
  {
    bool motionDetected = false;

    // -------- LED 1 --------
    if (irState1 == HIGH)
    {
      digitalWrite(ledPin1, HIGH);
      motionDetected = true;
    }
    else
    {
      digitalWrite(ledPin1, LOW);
    }


    // -------- LED 2 --------
    if (irState2 == HIGH)
    {
      analogWrite(ledPin2, 255);
      motionDetected = true;
    }
    else
    {
      analogWrite(ledPin2, 50);
    }


    // -------- LED 3 --------
    if (irState3 == HIGH)
    {
      analogWrite(ledPin3, 255);
      motionDetected = true;
    }
    else
    {
      analogWrite(ledPin3, 50);
    }


    // -------- LED 4 --------
    if (irState4 == HIGH)
    {
      digitalWrite(ledPin4, HIGH);
      motionDetected = true;
    }
    else
    {
      digitalWrite(ledPin4, LOW);
    }


    // -------- LED 5 --------
    if (irState5 == HIGH)
    {
      analogWrite(ledPin5, 255);
      motionDetected = true;
    }
    else
    {
      analogWrite(ledPin5, 50);
    }


    // -------- LED 6 --------
    if (irState6 == HIGH)
    {
      digitalWrite(ledPin6, HIGH);
      motionDetected = true;
    }
    else
    {
      digitalWrite(ledPin6, LOW);
    }


    // -------- LCD --------
    lcd.clear();

    if (motionDetected)
    {
      lcd.setCursor(0, 0);
      lcd.print("MOTION DETECTED");

      lcd.setCursor(0, 1);
      lcd.print("LIGHTS ON");
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("NO MOTION");

      lcd.setCursor(0, 1);
      lcd.print("DIM LIGHT");
    }
  }


  // ==================================================
  // DAYLIGHT CONDITION
  // ==================================================

  else
  {
    // Turn OFF all LEDs
    digitalWrite(ledPin1, LOW);
    analogWrite(ledPin2, 0);
    analogWrite(ledPin3, 0);
    digitalWrite(ledPin4, LOW);
    analogWrite(ledPin5, 0);
    digitalWrite(ledPin6, LOW);

    // LCD
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("DAYTIME");

    lcd.setCursor(0, 1);
    lcd.print("LIGHTS OFF");
  }


  // Serial information
  Serial.print("IR1: ");
  Serial.print(irState1);

  Serial.print(" IR2: ");
  Serial.print(irState2);

  Serial.print(" IR3: ");
  Serial.print(irState3);

  Serial.print(" IR4: ");
  Serial.print(irState4);

  Serial.print(" IR5: ");
  Serial.print(irState5);

  Serial.print(" IR6: ");
  Serial.println(irState6);


  delay(1000);
}