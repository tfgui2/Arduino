#ifndef __RotaryEncoder_h_
#define __RotaryEncoder_h_
/*
  Rotary Encoder lib with no interrupt
*/

#include <Button.h>

class RotaryEncoder {
  public:
    RotaryEncoder(uint8_t clk, uint8_t dt, uint8_t sw, void (*rotate)(int direction), void (*click)()) {
      m_pin1 = clk;
      m_pin2 = dt;
      pinMode(m_pin1, INPUT_PULLUP);
      pinMode(m_pin2, INPUT_PULLUP);
      onRotate = rotate;

      m_bt = new Button(sw, click);
    }

    void run() {
      int dir = getDirection();
      if (dir != 0) {
        onRotate(dir);
      }

      m_bt->run();
    }

  private:
    uint8_t m_pin1;
    uint8_t m_pin2;
    int state = 0;
    int getDirection();
    void (*onRotate)(int direction);

    Button* m_bt;
};

#endif //__MyEncoder_h_
