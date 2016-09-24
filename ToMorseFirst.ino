byte pin = 15;
int period = 225;

byte table[] = {
                65 // A
              , 136 // B
              , 138 // C
              , 100 // D
              , 32 // E
              , 130 // F
              , 102 // G
              , 128 // H
              , 64 // I
              , 135 // J
              , 101 // K
              , 132 // L
              , 67 // M
              , 66 // N
              , 103 // O
              , 134 // P
              , 141 // Q
              , 98 // R
              , 96 // S
              , 33 // T
              , 97 // U
              , 129 // V
              , 99 // W
              , 137 // X
              , 139 // Y
              , 140 // Z
                };
byte countOfLetters = 26;

void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(57600);
}



void loop() { 
  if (Serial.available() > 0) {
    byte letter = byte(Serial.read());
  
    if (letter < 'A' || letter > 'Z') {
      return;
    }
  
    letter -= 'A';
    
    byte actions = table[letter];
    byte countOfAction = actions >> 5;
    
    actions ^= (actions >> countOfAction) << countOfAction;
  
    byte count = 0;
  
    byte k = actions;
  
    while (k > 0) {
      count++;
      k >>= 1;
    }
    
    getBin(countOfAction, actions);
  }
}

void getBin(byte bits, byte n) {
  byte k = bits;
  byte bitt;

  while (k > 0) {
    k--;
    bitt = (n & (1 << k)) == 0 ? 0 : 1;
    
    if (bitt == 0) {
      toBlink(period);  
    } else {
      toBlink(3 * period);
    }

    notBlink(period);
  }

  notBlink(3 * period);
}

void toBlink(int i) {
  digitalWrite(pin, HIGH);
  delay(i);
}

void notBlink(int i) {
  digitalWrite(pin, LOW);
  delay(i);
}
