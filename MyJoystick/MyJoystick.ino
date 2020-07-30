/*
 * Arduino Leonardo or Pro mini only
 */
#include <Joystick.h>
Joystick_ Joystick;

void setup() {
  
  // button rows (output)
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // button cols (Input)
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  // 3 switch
  pinMode(14, OUTPUT);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  
  digitalWrite(14, LOW);

  // Initialize Joystick Library
  Joystick.begin();

  Serial.begin(9600);
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 9;

// Last state of the button
int lastButtonState[2][4] = {{0,0,0,0}
                            ,{0,0,0,0}};
int mode = 0;

void loop() {
  // Read switch
  int m1 = !digitalRead(15);
  int m2 = !digitalRead(16);
  if (m1) 
  { mode = 2; }
  else if (m2)
  { mode = 0; }
  else 
  { mode = 1; }
  
  
  // Read buttons
  for (int row = 0; row < 2; row++)
  {
    digitalWrite(row + 2, LOW);
    for (int col = 0; col < 4; col++)
    {
        int currentButtonState = !digitalRead(col + 4);
        if (currentButtonState != lastButtonState[row][col])
        {
          int index = (row * 4) + col + (mode * 8);
          Joystick.setButton(index, currentButtonState);
          lastButtonState[row][col] = currentButtonState;
        }
    }
    digitalWrite(row + 2, HIGH);
  }
  
  delay(50);
}
