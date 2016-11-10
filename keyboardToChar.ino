byte pinButton[] = { 2, 3, 4, 5, 6 };
byte pinShift = 10;

boolean shift = false;
boolean escape = false;

int head = 0;
int sizeKey = 200;

byte keys[200];

char ita2[] = {
    // letters part
    '\0','T', '\r','O', ' ', 'H', 'N', 'M',
    '\n','L', 'R', 'G', 'I', 'P', 'C', 'V',
    'E', 'Z', 'D', 'B', 'S', 'Y', 'F', 'X',
    'A', 'W', 'J', '\x0E', 'U', 'Q', 'K', '\x1B',
    // figures part
    '\0','5', '\r','9', ' ', '#', ',', '.',
    '\n',')', '4', '&', '8', '0', ':', '=',
    '3', '+', ';', '?', '\'','6', '!', '/',
    '-', '2', '"', '\b', '7', '1', '(', '\x0F' };

void setup() {
  Serial.begin(57600);

  for (byte pin : pinButton) {
    pinMode(pin, INPUT_PULLUP);  
  }

  pinMode(pinShift, OUTPUT);
}

void shiftMode() {
  if (shift) {
    digitalWrite(pinShift, LOW);
  } else {
    digitalWrite(pinShift, HIGH);
  }
  
  shift = !shift;  
}

void loop() {
  readKey();

  if (canGetKey()) {
    getKey();
  }
  
  delay(1);
}

boolean canGetKey() {
  for (int i = 1; i < sizeKey; i++) {
    if (keys[i] != keys[i - 1]) {
      return false;
    }
  }

  return true;
}

void readKey() {
  byte key = 0;
  
  for (byte button : pinButton) {
    key <<= 1;
    
    if (digitalRead(button) == LOW) {
      key += 1;    
    }
  }

  keys[head] = key;

  head += 1;
  head %= sizeKey;
}

void getKey() {
  byte key = keys[head];

  for (int i = 0; i < sizeKey; i++) {
    keys[i] = 0;
  }
  
  if (key != 0) {
    if (shift) {
      key += 1 << 5;  
    }

    char charNow = ita2[key];

    if (charNow == '\x0E') {
      shiftMode();
      escape = true;
    } else if (charNow == '\x0F') {
      shiftMode();
      escape = false;
    } else if (charNow == '\x1B') {
      escape = false;
      shiftMode();
    } else {
      Serial.println(charNow);

      if (escape) {
        escape = false;

        shiftMode();
      }
    }
  }
}
