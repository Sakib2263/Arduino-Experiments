void setup() {

  for (int pin = 2; pin < 14; pin++) {
    pinMode(pin, OUTPUT);
  }

}

void loop() {
  int t = 300;
  digitalWrite(10, HIGH);
  //--> sequential on off
  for (int i = 2; i < 10; i++) {
    digitalWrite(i, HIGH);
    delay(t);
  }
  for (int i = 2; i < 10 ; i++) {
    digitalWrite(i, LOW);
    delay(t);
  }

  delay(1000);
  digitalWrite(11, HIGH);

  // 1--> on..off -->2 on off
  for (int i = 2; i < 10; i++) {
    digitalWrite(i, HIGH);
    delay(t);
    digitalWrite(i, LOW);
    delay(t);
  }
  for (int i = 9; i > 1 ; i--) {
    digitalWrite(i, HIGH);
    delay(t);
    digitalWrite(i, LOW);
    delay(t);
  }
  delay(1000);
  t = 200;
  digitalWrite(12, HIGH);
  //pattern 0
  for (int j = 0 ; j < 2; j++) {
    for (int i = 2; i < 10; i++) {
      digitalWrite(i, HIGH);
      digitalWrite(10 - i, HIGH);
      delay(t);
      digitalWrite(i, LOW);
      digitalWrite(10 - i, LOW);
      delay(t);
    }
  }
  delay(1000);
  digitalWrite(13, HIGH);
  //patttern 1
  t = 60;
  for (int j = 0 ; j < 2; j++) {
//    ------ >
    for (int i = 2; i < 9; i++) {
      digitalWrite(i, HIGH);
      delay(t);
      digitalWrite(i + 1, HIGH);
      delay(t);
      digitalWrite(i + 2, HIGH);
      delay(t);
      digitalWrite(i, LOW);
      //delay(t);
      digitalWrite(i + 1, LOW);
    }
    //<-----
    for (int i = 9; i > 1; i--) {
      digitalWrite(i, HIGH);
      delay(t);
      digitalWrite(i - 1, HIGH);
      delay(t);
      digitalWrite(i - 2, HIGH);
      delay(t);
      digitalWrite(i, LOW);
      //delay(t);
      digitalWrite(i - 1, LOW);

    }
  }
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(1000);


  /*/ -.-.-.>> odd
    t=500;
    for (int i = 2; i < 14; i+=2) {
      //int b = random(i, 13);
      digitalWrite(i, HIGH);
      delay(t);

    }

    for (int i = 2; i < 14; i+=2) {
      //int b = random(i, 13);
      digitalWrite(i, LOW);
      delay(t);
    }
    //.-.-.->>even
      for (int i = 3; i < 14; i+=2) {
      //int b = random(i, 13);
      digitalWrite(i, HIGH);
      delay(t);

    }

    for (int i = 3; i < 14; i+=2) {
      //int b = random(i, 13);
      digitalWrite(i, LOW);
      delay(t);
    }*/

}
