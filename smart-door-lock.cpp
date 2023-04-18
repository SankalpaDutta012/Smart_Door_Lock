#include <Servo.h>
#include <Keypad.h>

Servo lock;
const int lockPin = 9;

// Define keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define password
const char* password = "1234";

void setup() {
  Serial.begin(9600);
  lock.attach(lockPin);
  lock.write(0);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key);
    if (key == '#') {
      // Check password
      if (checkPassword()) {
        // Unlock door
        lock.write(90);
        delay(1000);
        lock.write(0);
      }
    }
  }
}

bool checkPassword() {
  String enteredPassword = "";
  char key;
  do {
    key = keypad.getKey();
    if (key != NO_KEY) {
      enteredPassword += key;
    }
  } while (key != '#' && enteredPassword.length() < 4);
  
  Serial.println(enteredPassword);
  
  return enteredPassword.equals(password);
}
