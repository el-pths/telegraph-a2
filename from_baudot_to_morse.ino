byte pinButton[] = { 2, 3, 4, 5, 6 };
byte pinShift = 10;
byte pinBlink = 14;

boolean shift = false;
boolean escape = false;

int head = 0;
int tail = 0;
int blinks[200];
int blinksSize = 200;
int ledState = LOW;
unsigned long previousMillis = 0;
long interval = 0;
int period = 225;

byte key;
bool keyRead;

char ita2[] = {
    // letters part
    0, 'T', 0, 'O', ' ', 'H', 'N', 'M',
    0, 'L', 'R', 'G', 'I', 'P', 'C', 'V',
    'E', 'Z', 'D', 'B', 'S', 'Y', 'F', 'X',
    'A', 'W', 'J', '\x0E', 'U', 'Q', 'K', '\x1B',
    // figures part
    0, '5', 0, '9', ' ', 0, ',', '.',
    0, ')', '4', 0, '8', '0', ':', 0,
    '3', 0, ';', '?', 0,'6', '!', '/',
    '-', '2', '"', 0, '7', '1', '(', '\x0F' };

void setup() {
  Serial.begin(57600);

  for (byte pin : pinButton) {
    pinMode(pin, INPUT_PULLUP);  
  }

  pinMode(pinShift, OUTPUT);
  pinMode(pinBlink, OUTPUT);
  
  keyRead = false;
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
  byte reads = readKey();

  if (reads != 0) {
    key = max(reads, key);
    keyRead = true;
  } else {
    if (keyRead) {
      getKey(key);
      key = 0;
    }
  }

  if (head != tail) {
    blinkFunc();
  }
  
  delay(1);
}

void blinkFunc() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    tail++;
    tail %= blinksSize;

     
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    
    if (tail != head) {
      interval = blinks[tail];
    } else {
      interval = 0;
      ledState = LOW;
    }

    digitalWrite(pinBlink, ledState);
  }
}

byte readKey() {
  byte reads = 0;
  
  for (byte button : pinButton) {
    reads <<= 1;
    
    if (digitalRead(button) == LOW) {
      reads += 1;    
    }
  }

  return reads;
}

void getKey(byte keyNow) {
  if (keyNow != 0) {
    if (shift) {
      keyNow += 1 << 5;  
    }

    char charNow = ita2[keyNow];

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
      if (charNow != 0) {
        Serial.println(charNow);
        addBlinks(charNow);
      }
      
      if (escape) {
        escape = false;

        shiftMode();
      }
    }
  }
}

void add(int T) {
  blinks[head] = T;
  head++;
  blinks[head] = period;
  head++;
}

void b() {
  add(3 * period);
}

void d() {
  add(period);
}

void addBlinks(char c) {
  switch (c) {
      case 'T':
      {
        b();
      }
        break;
      case 'O':
      {
        b();
        b();
        b();
      }
        break;
      case 'H':
      {
        d();
        d();
        d();
        d();
      }
        break;
      case 'N':
      {
        b();
        d();
      }
        break;
      case 'M':
      {
        b();
        b();
      }
        break;
      case 'L':
      {
        d();
        b();
        d();
        d();
      }
        break;
      case 'R':
      {
        d();
        b();
        d();
      }
        break;
      case 'G':
      {
        b();
        b();
        d();
      }
        break;
      case 'I':
      {
        d();
        d();
      }
        break;
      case 'P':
      {
        d();
        b();
        b();
        d();
      }
        break;
      case 'C':
      {
        b();
        d();
        b();
        d();
      }
        break;
      case 'V':
      {
        d();
        d();
        d();
        b();
      }
        break;
      case 'E':
      {
        d();
      }
        break;
      case 'Z':
      {
        b();
        b();
        d();
        d(); 
      }
        break;
      case 'D':
      {
        b();
        d();
        d();
      }
        break;
      case 'B':
      {
        b();
        d();
        d();
        d();
      }
        break;
      case 'S':
      {
        d();
        d();
        d();
      }
        break;
      case 'Y':
      {
        b();
        d();
        b();
        b();
      }
        break;
      case 'F':
      {
        d();
        d();
        b();
        d();
      }
        break;
      case 'X':
      {
        b();
        d();
        d();
        b();
      }
        break;
      case 'A':
      {
        d();
        b();
      }
        break;
      case 'W':
      {
        d();
        b();
        b();
      }
        break;
      case 'J':
      {
        d();
        b();
        b();
        b();
      }
        break;
      case 'U':
      {
        d();
        d();
        b();
      }
        break;
      case 'Q':
      {
        b();
        b();
        d();
        b();
      }
        break;
      case 'K':
      {
        b();
        d();
        b();
      }
        break;
      case '5':
      {
        d();
        d();
        d();
        d();
        d();
      }
        break;
      case '9':
      {
        b();
        b();
        b();
        b();
        d();
      }
        break;
      case ' ':
      {
        b();
      }
        break;
      case ',':
      {
        d();
        b();
        d();
        b();
        d();  
        b();
        
      }
        break;
      case '.':
      {
        d();
        d();
        d();
        d();
        d();
        d();
      }
        break;
      case ')':
      {
        b();
        d();
        b();
        b();
        d();
        b();
      }
        break;
      case '4':
      {
        d();
        d();
        d();
        d();
        b();
      }
        break;
      case '8':
      {
          b();
          b();
          b();
          d();
          d();
      }
        break;
      case '0':
      {
        b();
        b();
        b();
        b();
        b();
      }
        break;
      case ':':
      {
        b();
        b();
        b();
        d();
        d();
        d();
      }
        break;
      case '3':
      {
        d();
        d();
        d();
        b();
        b();
      }
        break;
      case ';':
      {
        b();
        d();
        b();
        d();  
        b();
      }
        break;
      case '?':
      {
        d();
        d();
        b();
        b();
        d();
        d();
      }
        break;
      case '6':
      {
        b();
        d();
        d();
        d();
        d();
      }
        break;
      case '!':
      {
        b();
        b();
        d();
        d();
        b();
        b();
      }
        break;
      case '/':
      {
        b();
        d();
        d();
        b();
        d();
      }
        break;
      case '-':
      {
        b();
        d();
        d();
        d();
        d();
        b();
      }
        break;
      case '2':
      {
        d();
        d();
        b();
        b();
        b();
      }
        break;
      case '"':
      {
        d();
        b();
        d();
        d();
        b();
        d();
      }
        break;
      case '7':
      {
        b();
        b();
        d();
        d();
        d();
      }
        break;
      case '1':
      {
        d();
        b();
        b();
        b();
        b();
      }
        break;
      case '(':
      {
        b();
        d();
        b();
        b();
        d();
        b();
      }
        break;
  }
}

