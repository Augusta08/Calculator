#include <LiquidCrystal.h>
#include <Keypad.h>
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int ROWS = 4;
const int COLS = 4;
char keys[ROWS][COLS] = {
  { '7', '8', '9', '/' },
  { '4', '5', '6', '*' },
  { '1', '2', '3', '-' },
  { 'C', '0', '=', '+' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };      //connect to the row pinouts of the keypad
byte colPins[COLS] = { 13, 12, 11, 10 };  //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  lcd.begin(16, 2);
}


void loop() {
  static String userInput = "";
  char key = keypad.getKey();
  if (key) {  // Check if a key is pressed
    if (key == 'C') {
      lcd.clear();
      userInput = "";
    } else if (key == '=') {
      String plus = "+";
      String minus = "-";
      String times = "*";
      String div = "/";
      String Operation = "";
      int index;
      if (userInput.indexOf(div) != -1) {
        index = userInput.indexOf(div);
        Operation = "/";
      } else if (userInput.indexOf(times) != -1) {
        index = userInput.indexOf(times);
        Operation = "*";
      } else if (userInput.indexOf(plus) != -1) {
        index = userInput.indexOf(plus);
        Operation = "+";
      } else if (userInput.indexOf(minus) != -1) {
        index = userInput.indexOf(minus);
        Operation = "-";
      }

      // Extract the first part after the operation
      String operand1 = userInput.substring(0, index);

      // Extract the second part after the operation
      String operand2 = userInput.substring(index + 1);

      // Converting the operands from strings to float
      float oper1 = operand1.toFloat();
      float oper2 = operand2.toFloat();
      float result;
      if (Operation == "+") {
        result = oper1 + oper2;
      } else if (Operation == "-") {
        result = oper1 - oper2;
      } else if (Operation == "*") {
        result = oper1 * oper2;
      } else if (Operation == "/") {
        result = oper1 / oper2;
      }
      lcd.setCursor(0, 1);
      lcd.print(result);
      userInput = "";

    } else if (key != '=') {
      lcd.print(key);    // Display the key on the LCD
      userInput += key;  // Append key to userInput string if needed
    }
  }
}
