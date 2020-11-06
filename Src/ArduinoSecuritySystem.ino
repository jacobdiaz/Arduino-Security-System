// RFID Security System
int attempts;

// States
bool locked;
bool unlocked;
bool unlockedFailed;

// Media
String successSound = "/some-file-path.mp3";
String failureSound = "/some-file-path.mp3";

// LCD
String sitIdleMessage;
String successMessage;
String failureMessage;

void printMessage() {
  // Print message base on state.
}
void unlock() {
  // unlock mechanism - retract servo motor
  // Call 30 second timer
  // lock mechanism
}
void lock() {
  // extend servo motor
}
void readCard() {
  // isCardValid()
  // If id card is true... unlock(), printMessage(), playMedia(successmp3)
  // if not... printMessage() failure and playMedia(failure.mp3), buzz()
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
}

void loop() {
  // if there is a card input readCard()
}
