#include <Stepper.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// initialize the stepper library on pins 8 through 11:

LiquidCrystal lcd(13, 12, 5, 4, 3, 2); //LCD output from from pins

int sensorReading = 15; //enter intended speed, change negative and positve to change directions

const int buttonPin = 6; //button inputs to pin 6

int buttonState = 0; // variable for button

void setup()

{
  pinMode(buttonPin, INPUT); // sets up the button
  lcd.begin(16, 2);
  lcd.clear();
  Wire.begin();
  Wire.write(sensorReading);
}


const int stepsPerRevolution = 1000;  // amount of steps in the motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // motor connected to these pins

byte x=2;

void loop()
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) //if button is pressed
  {
    sensorReading = -sensorReading; //then motor reverses direction
    lcd.clear();

  
  }

  int motorSpeed = sensorReading; // using different variables for the purpose of flexibility

  //motor speed codeblock

  if (motorSpeed > 0) {
    x = 1;
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    myStepper.setSpeed(motorSpeed);
    myStepper.step(stepsPerRevolution / 100); // if speed is greater than zero, print biceps
    lcd.setCursor(0,0);
    lcd.print("biceps");
  }

  if (motorSpeed < 0) {
    x = 0;
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    myStepper.setSpeed(-motorSpeed);
    myStepper.step(-stepsPerRevolution / 100); // if speed is less than zero print triceps
    lcd.setCursor(0, 0);
    lcd.print("triceps");
  }

  lcd.setCursor(0, 1);
  lcd.print(motorSpeed);


}



