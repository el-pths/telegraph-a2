byte button1 = 6;
byte button2 = 5;
byte button3 = 4;
byte button4 = 3;
byte button5 = 2;


void setup() {
  Serial.begin(57600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
}

void loop() {
  getKey();
  
  delay(2000);
}

void getKey() {
  boolean keyboard[] = {false, false, false, false, false};

  boolean flag = false;
  
  if (digitalRead(button1) == LOW) {
    keyboard[0] = true;
    flag = true;
  }
  
  if (digitalRead(button2) == LOW) {
    keyboard[1] = true;
    flag = true;
  }
  
  if (digitalRead(button3) == LOW) {
    keyboard[2] = true;
    flag = true;
  }
  
  if (digitalRead(button4) == LOW) {
    keyboard[3] = true;
    flag = true;
  }

  if (digitalRead(button5) == LOW) {
    keyboard[4] = true;
    flag = true;
  }

  if (flag) { 
    for (int i = 0; i < 5; i++) {
      Serial.print(keyboard[i]);
      Serial.print(" ");
    } 
    Serial.println();
  }
}

