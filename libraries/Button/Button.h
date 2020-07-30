#ifndef __BUTTON_H_
#define __BUTTON_H_
/*
   Button pin + callback
*/

class Button {
  public:
    Button(uint8_t pin, void (*fp)()) {
      m_pin = pin;
      pinMode(m_pin, INPUT_PULLUP);
      onPress = fp;
    }

    void run()
    {
      long elapsedTime = millis() - m_lastdebounce;
      if (elapsedTime < 10) {
        return;
      }
      m_lastdebounce = millis();

      int state = digitalRead(m_pin);
      if (m_state == HIGH && state == LOW) {
        onPress();
      }
      m_state = state;
    }

  private:
    uint8_t m_pin;
    int m_state = HIGH;
    void (*onPress)();
    long m_lastdebounce = 0;
};

#endif // __BUTTON_H_
