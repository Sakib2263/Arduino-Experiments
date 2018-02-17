int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;          // the PWM pins the LEDs are attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 2;    // how many points to fade the LED by

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  if (brightness < 256) analogWrite(led1, brightness);
  if (brightness > 63)  analogWrite(led2, brightness - 64);     //starts lighting up when led1 is lit 1/4
  if (brightness > 127)  analogWrite(led3, brightness - 128);   //when led1 is 2/4
  if (brightness > 191)  analogWrite(led4, brightness - 192);   //when led1 is 3/4

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  // 255 + 64 + 64 + 64 = 447
  // led4 starts at 192, ends at 192 + 255 = 447

  if (brightness <= 0 || brightness >= 447) {
    fadeAmount = -fadeAmount;
  }
  // wait for 10 milliseconds to see the dimming effect
  delay(10);
}
