int pin1 = 4;
int pin2 = 5;
int speedpin = 6;

int pin1b = 8;
int pin2b = 9;
int speedpinb = 10;


int motorspeed = 255;

void setup() {
  // put your setup code here, to run once:
pinMode(speedpin, OUTPUT);
pinMode(pin1, OUTPUT);
pinMode(pin2, OUTPUT);

pinMode(speedpinb, OUTPUT);
pinMode(pin1b, OUTPUT);
pinMode(pin2b, OUTPUT);

motornr();
motornrb();
delay(5000);

motorstop();
motorstopb();
delay(5000);

motorbr();
motorbrb();
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void motornr()
{
  analogWrite(speedpin, motorspeed);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}
void motorbr()
{
  analogWrite(speedpin, motorspeed);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}
void motorstop()
{
  analogWrite(speedpin, 0);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

void motornrb()
{
  analogWrite(speedpinb, motorspeed);
  digitalWrite(pin1b, HIGH);
  digitalWrite(pin2b, LOW);
}
void motorbrb()
{
  analogWrite(speedpinb, motorspeed);
  digitalWrite(pin1b, LOW);
  digitalWrite(pin2b, HIGH);
}
void motorstopb()
{
  analogWrite(speedpinb, 0);
  digitalWrite(pin1b, LOW);
  digitalWrite(pin2b, LOW);
}
