#include "Arduino.h"
#include "Buzzer.h"
#include "LiquidCrystal.h"
#include "RFID.h"
#include "Servo.h"
#include "SpeakerStereo3W.h"

#define BUZZER_PIN_SIG  2
#define LCD_PIN_RS  8
#define LCD_PIN_E 7
#define LCD_PIN_DB4 3
#define LCD_PIN_DB5 4
#define LCD_PIN_DB6 5
#define LCD_PIN_DB7 6
#define RFID_PIN_RST  9
#define RFID_PIN_SDA  10
#define SERVO9G_PIN_SIG A3
#define STEREOSPEAKER_PIN_POS A4

// RFID system initializer
RFID rfid(RFID_PIN_SDA,RFID_PIN_RST);
// LCD initializer
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
// Servo initializer
Servo servo9g;
// Buzzer
Buzzer buzzer(BUZZER_PIN_SIG);
// Speaker
SpeakerStereo3W StereoSpeaker(STEREOSPEAKER_PIN_POS);


// Global variables
const int servo9gRestPosition   = 20;  //Starting position
const int servo9gTargetPosition = 150; //Position when event is detected
unsigned int StereoSpeakerHoorayLength          = 6;                                                      // amount of notes in melody
unsigned int StereoSpeakerHoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int StereoSpeakerHoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!
int attempts;

// States
bool locked;
bool unlocked;
bool unlockedFailed;

// LCD
String sitIdleMessage = "Please scan card";
String successMessage = "Access Granted";
String failureMessage = "Access Denied";

void printMessage() {
  // Print message base on state.
  if (locked && !unlocked) {
    lcd.print(sitIdleMessage);
  } else if (!locked && unlocked) {
    lcd.print(successMessage);
  } else  if (unlockedFailed) {
    lcd.print(failureMessage);
  }
}

void unlock() {
  // unlock mechanism - retract servo motor
  // Call 30 second timer
  // lock mechanism
  myservo.write(10); // unlock
}
void lock() {
  // extend servo motor
}
void readCard() {
  // isCardValid()
  // If id card is true... unlock(), printMessage(), playMedia(successmp3)
  // if not... printMessage() failure and playMedia(failure.mp3), buzz()
  
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
}
bool isCardValid() {
  // Determine if card is valid
}
void playMedia(String path) {
  // Switch case
  // Based on success or failure determine which sound to play
  // Play the corresponding
}
void buzz() {
  // Activate a buzz
}

void setup() {
  // Setup LCD
  // Setup servo motor
  // setup RFID Reader
  // Setup Buzzer
  // Setup Speaker
  Serial.begin(9600);
  lcd.begin(16,2);
  rfid.init();
  servo9g.attach(SERVO9G_PIN_SIG);
  servo9g.write(servo9gRestPosition);
  printMessage();
  Serial.println(sitIdleMessage);
}

void loop() {
  // if there is a card input readCard()
}
