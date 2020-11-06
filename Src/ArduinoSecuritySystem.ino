#include <MFRC522.h>
#include <LiquidCrystal.h>

// RFID system initializer
MFRC522 mfrc522(10,9);
// LCD initializer
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
// Servo initializer
Servo myservo;

// RFID Security System attempts
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
  SPI.begin();
  lcd.begin(16,2);
  myservo.attach(8);
  myservo.write(170);
  printMessage();
  mfrc522.PCD_Init();
  Serial.println(sitIdleMessage);
}

void loop() {
  // if there is a card input readCard()
  readCard
}
