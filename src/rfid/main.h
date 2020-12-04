#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9
#define LCD_PIN_RS  8
#define LCD_PIN_E 7
#define LCD_PIN_DB4 3
#define LCD_PIN_DB5 4
#define LCD_PIN_DB6 5
#define LCD_PIN_DB7 6

// Setup RFID and LCD
RFID rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_DB4, LCD_PIN_DB5, LCD_PIN_DB6, LCD_PIN_DB7);

// Array of Valid IDs
int const validIdsSize = 1;
String validIds[validIdsSize] = {"102 81 23 41"};

// State
boolean cardRead = false;

// Input
String rfidCard;

// Attempts
int attempts = 3;
String welcomeMessage = "Welcome Back";
String deniedMessage  = "Incorrect ID...";
// Read RFID Input
void readInput() {
  if (rfid.isCard()) {
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
  lcd.setCursor(0, 1);
  lcd.print("Access Denied");
  rfidCard = " ";
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(deniedMessage);
  lcd.setCursor(0, 1);
  lcd.print(attempts);
  lcd.print(" attempts left");
  --attempts;
  delay(4500);
  lcd.clear();
  cardRead = false; // reset state
}

// print message to LCD, unlock servoMotor, and reset attempts
void idAccepted() {
  // TODO Unlock Servo Motor
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
  // Checks if element in given array
int includes(const String store[], const int storeSize, const String query) {
  for (size_t i = 0; i < storeSize; ++i) {
    if (store[i] == query) {
      return i;
    }
  }
  return -1;
}
}
