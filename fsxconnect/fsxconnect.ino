// oled 
// pin: scl(A5) sda(A4)
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// button
#include <Button.h>
void button1Click();
Button bt1(8, button1Click);


// encoder
#include <RotaryEncoder.h>
void EncRotate(int dir);
void EncPush();
RotaryEncoder enc(2, 3, 4, EncRotate, EncPush);



// internal val
int led = 13;
bool isUpdate = true;

char text[][10] =
{
  "AutoPilot", // max 9 char
  "Audio",
  "Com 1",
  "Com 2",
  "Nav 1",
  "Nav 2",
};
enum MODE
{
  MODE_AP,
  MODE_AUDIO,
  MODE_COM1,
  MODE_COM2,
  MODE_NAV1,
  MODE_NAV2,
  MODE_MAX
};
int modeIndex = 0;
int showMenu = 0; // 0 menu, 1 sub
char encval2[10] = "";

#include "ClientEvents.h"


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  // display
  delay(1000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
}

void loop() {
  bt1.run();
  enc.run();

  if (isUpdate)
  {
    isUpdate = false;
    if (showMenu) {
      displayMenu();
    }
    else {
      displayText();
    }
  }

  delay(1);
}

void displayText()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(5, 0);
  display.print(text[modeIndex]);

  display.setCursor(5, 17);
  display.print(encval2);

  display.display();
}

void displayMenu()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  char tet[][3] = {
    "ap", "ad", "c1", "c2", "n1", "n2",
  };
  int index = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      int x = j * 39 + 5;
      int y = i * 17;
      display.setCursor(x, y);
      if (index == modeIndex) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      }
      else {
        display.setTextColor(SSD1306_WHITE);
      }
      display.print(tet[index]);
      index++;
    }
  }

  display.display();
}


void button1Click()
{
  showMenu = !showMenu;
  isUpdate = true;
}

void MenuRotate(int dir) {
  modeIndex = (modeIndex + MODE_MAX + dir) %  MODE_MAX;
  isUpdate = true;
}

void EncRotate(int dir)
{
  if (showMenu) {
    MenuRotate(dir);
    return;
  }
  
  int key = -1;
  bool alt = dir > 0;

  switch (modeIndex) {
    case MODE_AP:

      break;

    case MODE_AUDIO:
      break;

    case MODE_COM1:
      key = alt ? COM_RADIO_WHOLE_INC : COM_RADIO_WHOLE_DEC;
      break;

    case MODE_COM2:
      key = alt ? COM2_RADIO_WHOLE_INC : COM2_RADIO_WHOLE_DEC;
      break;

    case MODE_NAV1:
      key = alt ? NAV1_RADIO_WHOLE_INC : NAV1_RADIO_WHOLE_DEC;
      break;

    case MODE_NAV2:
      key = alt ? NAV2_RADIO_WHOLE_INC : NAV2_RADIO_WHOLE_DEC;
      break;
  }

  if (key > -1) {
    Serial.write(key);
  }

  sprintf(encval2, "value:%d", dir);
  isUpdate = true;
}

void EncPush()
{
  int key = -1;

  switch (modeIndex) {
    case MODE_AP:
      break;

    case MODE_AUDIO:
      break;

    case MODE_COM1:
      key = COM_STBY_RADIO_SWAP;
      break;

    case MODE_COM2:
      key = COM2_RADIO_SWAP;
      break;

    case MODE_NAV1:
      key = NAV1_RADIO_SWAP;
      break;

    case MODE_NAV2:
      key = NAV2_RADIO_SWAP;
      break;
  }

  if (key > -1) {
    Serial.write(key);
  }
}
