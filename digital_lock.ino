#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

#define BUZZER 6

LiquidCrystal_I2C lcd(32, 16, 2);

const byte ROWS = 4;
const byte COLUMNS = 3;
char hexaKeys[ROWS][COLUMNS] = {
 {'1', '2', '3'},
 {'4', '5', '6'},
 {'7', '8', '9'},
 {'*', '0', '#'}
};

byte rowPins[ROWS] = {12, 11, 10, 9};
byte columnPins[COLUMNS] = {8, 7, 4};
char keypressed;

String password="1234";
String tempPassword;
boolean locked = true;
int wrongPasswordCount = 0; 

Servo myservo;
int closedServoPosition = 57; 
int openServoPosition = 225;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  for (byte row = 0; row < ROWS; row++) 
  {
   pinMode(rowPins[row], OUTPUT);
   digitalWrite(rowPins[row], HIGH);
  }
  for (byte column = 0; column < COLUMNS; column++) 
  {
   pinMode(columnPins[column], INPUT_PULLUP);
  }
  myservo.attach(5);

}

void loop() {
  if (locked) {
    myservo.write(closedServoPosition);
    enterPassword();
  }
  while (!locked) {
    myservo.write(openServoPosition); 
    char input = getKeyFromKeypad();
    if (input == '*') {
      locked = true;
      delay(200);
    }
  }
}

char getKeyFromKeypad() {
 for (byte row = 0; row < ROWS; row++) {
   digitalWrite(rowPins[row], LOW);
   for (byte column = 0; column < COLUMNS; column++) {
     if (digitalRead(columnPins[column]) == LOW) {
       delay(50);
       while (digitalRead(columnPins[column]) == LOW) {
       }
       digitalWrite(rowPins[row], HIGH);
       return hexaKeys[row][column];
     }
   }
   digitalWrite(rowPins[row], HIGH);
 }
 return '\0';
}

void enterPassword() {
  int k = 5;
  int keysEntered = 0;
  int wrongAttempts = 0; 

  tempPassword = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" *** LOCKED *** ");
  lcd.setCursor(0, 1);
  lcd.print("Pass>");

  while (locked) {
    keypressed = getKeyFromKeypad();
    if (keypressed != NO_KEY) {
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
          keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
          keypressed == '8' || keypressed == '9' || keypressed == '#' || keypressed == '*') {
        tempPassword += keypressed;
        lcd.setCursor(k, 1);
        lcd.print("*");
        k++;
        keysEntered++;

        if (keysEntered == 4) {
          if (tempPassword == password) {
            Serial.println("unlocked");
            tone(BUZZER, 250, 200);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(" *** UNLOCKED *** ");
            locked = false;
          } else {
            tone(BUZZER, 500, 100);
            lcd.setCursor(0, 1);
            lcd.print("Wrong! Try Again");
            wrongAttempts++;

            if (wrongAttempts == 5) {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" *** HAHA *** ");
              playRickRoll(); 
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" *** LOCKED *** ");
              lcd.setCursor(0, 1);
              lcd.print("Pass>");
              keysEntered = 0;
              tempPassword = "";
              k = 5;
              wrongAttempts = 0; 
            } else {
              Serial.print("wrong: ");
              Serial.println(wrongAttempts);
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" *** LOCKED *** ");
              lcd.setCursor(0, 1);
              lcd.print("Pass>");
              keysEntered = 0;
              tempPassword = "";
              k = 5;
            }
          }
        }
      }
    }
  }
}

void playRickRoll() {
  int tonePin = 6;
  Serial.println("rick roll");
   tone(tonePin, 554, 559.204375);
    delay(621.338194444);
    delay(4.56866319444);
    tone(tonePin, 622, 579.763359375);
    delay(644.181510417);
    delay(4.56866319444);
    tone(tonePin, 415, 374.173515625);
    delay(415.748350694);
    delay(4.56866319444);
    tone(tonePin, 622, 629.104921875);
    delay(699.00546875);
    delay(4.56866319444);
    tone(tonePin, 698, 493.415625);
    delay(548.239583333);
    delay(82.2359375);
    tone(tonePin, 830, 86.347734375);
    delay(95.9419270833);
    delay(4.56866319444);
    tone(tonePin, 739, 82.2359375);
    delay(91.3732638889);
    delay(9.13732638889);
    tone(tonePin, 698, 69.900546875);
    delay(77.6672743056);
    delay(45.6866319444);
    tone(tonePin, 554, 703.117265625);
    delay(781.24140625);
    delay(4.56866319444);
    tone(tonePin, 622, 592.09875);
    delay(657.8875);
    delay(4.56866319444);
    tone(tonePin, 415, 1151.303125);
    delay(1279.22569444);
    delay(479.709635417);
    tone(tonePin, 830, 86.347734375);
    delay(95.9419270833);
    delay(4.56866319444);
}