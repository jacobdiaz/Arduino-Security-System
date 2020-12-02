// To be able to use RFID.h, you have to include the .zip file
// Sketch > Library > Include Zip > RFID.zip
// ID of keychain : 153 74 198 184
// ID of card :     102 81 23 41

// Pin Definitions
#include "LiquidCrystal.h"
#include <SPI.h>
#include <RFID.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LCD_PIN_RS  8
#define LCD_PIN_E 7
#define LCD_PIN_DB4 3
#define LCD_PIN_DB5 4
#define LCD_PIN_DB6 5
#define LCD_PIN_DB7 6
#define SERVO_PIN A3
#define BUZZ_PIN 2
#define STEROSPEAKER_PIN A4

// Setup RFID and LCD and servo
RFID rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_DB4, LCD_PIN_DB5, LCD_PIN_DB6, LCD_PIN_DB7);
Servo servo;


// Array of Valid IDs
int const validIdsSize = 1;
String validIds[validIdsSize] = {"102 81 23 41"};

// State
boolean cardRead = false;
boolean disabled = false;

// Input
String rfidCard;

// Attempts
int attempts = 3;
String welcomeMessage = "Welcome Back";
String deniedMessage  = "Incorrect ID...";
int angle = 0;    

void unlock() {
  for (angle = 100; angle>=1; angle-=5) {    // Moves servo to open position        
    servo_test.write(angle);              
    delay(5);                       
  } 
}

<<<<<<< HEAD
void lock() {
  for (angle = 0; angle < 100; angle += 5) {    // Moves servo to locking position 
    servo_test.write(angle);                 
    delay(15);                       
  }   
}
=======
// Countdown
int countDown = 20;  // Countind down 2 minutes
unsigned long lastTick;
>>>>>>> e211db2b264ae8c08b2f7b9cab5f70292a3d32a2

void setup() {
  servo_test.attach(SERVO_PIN);
  Serial.begin(9600);
  lcd.begin(16, 2);
  SPI.begin();
  rfid.init();
}

void loop() {
  // Read if there is any RFID input, change state if input
  readInput();

  // Check to see if the read Input is in the validIDs array
  if ( cardRead == true && isValidId(rfidCard)) {
    idAccepted();
  }

  // Check to see if the read Input is NOT in the validIDs array
  if ( cardRead == true && !isValidId(rfidCard)) {
    idDenied(); // print message to LCD and decrement attempts
  }

  // 3 unsucessful attemps - Lockem out!
  if(attempts == 0){
      disabled = true;
      deniedLock(); // 10s lock
    }
  
}

// Read RFID Input
void readInput() {
  if (rfid.isCard() && !disabled) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
      cardRead = true;
    }
    rfid.halt();
  }

    
}

// print message to LCD and decrement attempts
void idDenied() {
  // TODO Make the buzzer BUZZ
  tone(BUZZ_PIN, 200, 1000);  // added buzzer
  lcd.setCursor(0, 1);
  lcd.print("Access Denied");
  rfidCard = " ";
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(deniedMessage);
  lcd.setCursor(0, 1);
  --attempts;
  lcd.print(attempts);
  lcd.print(" attempts left");
  delay(4500);
  lcd.clear();
  cardRead = false; // reset state
}

// print message to LCD, unlock servoMotor, and reset attempts
void idAccepted() {
  // TODO Unlock Servo Motor
  unlock();
  // TODO Play Mp3?
  lcd.setCursor(0, 1);
  lcd.print("Success!");
  rfidCard = " ";
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(welcomeMessage);
  attempts = 3;
  delay(5000);
  lcd.clear();
  displayIdleMessage();
  cardRead = false; // reset state
}

// Checks if param is in the validID array.
boolean isValidId(String ID) {
  if (includes(validIds, validIdsSize, ID) != -1) { // If it in the array
    Serial.println("Found ID in validIDs array");
    return true;
  }
  Serial.println("NOT found in validIDs array");// If it isn't in the array
  return false;
}

// Checks if element in given array
int includes(const String store[], const int storeSize, const String query) {
  for (size_t i = 0; i < storeSize; ++i) {
    if (store[i] == query) {
      return i;
    }
  }
  return -1;
}


//10s
void deniedLock(){
     unsigned long currentMillis = millis();
     lcd.setCursor(0,0);
     lcd.print("Device Disabled");
     
     if(currentMillis - lastTick >= 1000){
      if(countDown > 0 ){
        delay(1000);
        countDown--;
      } 
      
      if(countDown == 0){
        lcd.clear();
        cardRead = false; 
        disabled = false;
        attempts = 2;
        countDown = 20;
        displayIdleMessage();
        }
        
      if(disabled == true){  
      displayCountdown();
      lastTick += 1000;   
      }
  } 
  }

// Display IdleMessage when not being unlocked
void displayIdleMessage(){
        lcd.setCursor(0,0);
        lcd.print("Arduino Security");
        lcd.setCursor(0,1);
        lcd.print("Tap ID Here ->");
  }

// Displays a countdown to lcd
void displayCountdown(){
  int secs = countDown % 60;
  Serial.println(secs);
  Serial.print("Seconds");
  lcd.setCursor(0,1);
  lcd.print("Try again in: ");
  lcd.println(secs);
}
