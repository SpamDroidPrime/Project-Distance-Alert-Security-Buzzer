#include <LiquidCrystal.h>  // calling the library

/*------ Variable Declarations ------*/
int echoPin = 5;
int trigPin = 4;
int pingTravelTime;
int buzzPin = 6;

int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  //Creating own LiquidCrystal called "lcd", and defined all the pins used

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);  // telling the arduino that LCD has 16 columns and 2 rows of characters.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);

  Serial.begin(9600);  // start the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
  /*----- Sends an ultrasonic charp-----*/

  digitalWrite(trigPin, LOW);   // trig pin starts at low
  delayMicroseconds(10);        // delay of 10 microseconds
  digitalWrite(trigPin, HIGH);  // trig pin goes high
  delayMicroseconds(10);        // delay of 10 microseconds
  digitalWrite(trigPin, LOW);   // trig pin goes low

  pingTravelTime = pulseIn(echoPin, HIGH);  // measures how long the echo pin stays high and how long it take for it to go low and stors the value in pingTravelTime
  delay(25);

  // distance in cm
  int distanceCm = (pingTravelTime * 0.0343) / 2;  // distance in (cm)
  delay(500);

  lcd.setCursor(0, 0);                         // sets the cursor to (0,0) before printing
  if (distanceCm <= 0 || distanceCm >= 400) {  // checks for any negative numbers or numbers greater than 400 cm and changes the distanceCm to 999. Avoding any bad readings.
    distanceCm = 999;
  }

  if (distanceCm == 999) {  // if there's no object near the sensor, it will print "No object" and "Clear"
    lcd.print("No object       ");
    lcd.setCursor(0, 1);
    lcd.print("Clear           ");
    analogWrite(buzzPin, 0);  // No buzz sound
  } else {

    lcd.print("Dist: ");  // if there is object near the sensor it will print the distance in (cm)
    lcd.print(distanceCm);
    lcd.print(" cm    ");


    lcd.setCursor(0, 1);  // sets the cursor to second line of the LCD

    if (distanceCm > 30) {  // if distance is greater than 30, prints "safe" on lCD
      lcd.print("Status: Safe    ");
      analogWrite(buzzPin, 0);     // Still no buzz sound
    } else if (distanceCm > 15) {  // if distance is between 15-30cm, prints "Warning" on LCD
      lcd.print("Status: Warning ");
      analogWrite(buzzPin, 127);  // Medium buzzer sound
    } else {
      lcd.print("Status: ALERT!  ");  // if distance is between less than 15cm, prints "Alert" on LCD
      analogWrite(buzzPin, 255);      // Maximum buzzer sound
    }
  }
}
