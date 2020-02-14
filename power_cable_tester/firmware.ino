int outputs[] = {2,3,4,5,6,7,8,9};
int inputs[] = {A7,A6,A5,A4,A3,A2,A1,A0};

void setup() {
  Serial.begin(9600);
  
  for(int i=0; i<8; i++) {
    pinMode(outputs[i], OUTPUT);
    pinMode(inputs[i], INPUT_PULLUP);
  }

  Serial.println("Testing cable...");
  testReversed();
  testReversed10Pin();
  testShorts();
  testContinuity();
  
  Serial.println("Done.");
  solidGreen();
}

void allOff() {
  for(int i=0; i<8; i++) {
    digitalWrite(outputs[i],HIGH);
  }
}

void turnOn(int pin) {
  digitalWrite(outputs[pin], LOW);
}

void turnOff(int pin) {
  digitalWrite(outputs[pin], HIGH);
}

int isConnected(int pin) {
  return analogRead(inputs[pin]) < 500;
}

int notConnected(int pin) {
  return analogRead(inputs[pin]) > 500;
}

void printPins(int pin) {
  Serial.print(pin*2+1);
  Serial.print("-");
  Serial.print(pin*2+2);
}

void testReversed() {
  Serial.println(" Testing for 16 Pin Reverse...");
  bool reversed = true;
  allOff();
  for(int i=0; i<8; i++) {
    turnOn(i);
    if(notConnected(7-i)) reversed = false;
    turnOff(i);
  }
  if(reversed) {
    Serial.println(" REVERSED!");
    doubleFlash();
  }
  Serial.println(" not reversed.");
}

void testReversed10Pin() {
  Serial.println(" Testing for 10 Pin Reverse...");
  bool reversed = true;
  allOff();
  for(int i=0; i<5; i++) {
    turnOn(i);
    if(notConnected(4-i)) reversed = false;
    turnOff(i);
  }
  for(int i=5; i<8; i++) {
    turnOn(i);
    if(isConnected(i)) reversed = false;
    turnOff(i);
  }
  if(reversed) {
    Serial.println(" REVERSED!");
    doubleFlash();
  }
  Serial.println(" not reversed.");
}

void testShorts() {
  Serial.println(" Testing for Shorts...");
  bool failed = false;
  allOff();
  for(int i=0; i<8; i++) {
    turnOn(i);
    for(int j=0; j<8; j++) {
      if(i!=j) {
        if(isConnected(j)) {
          Serial.print("  Pins ");
          printPins(i);
          Serial.print(" short with ");
          printPins(j);
          Serial.println(". FAILED!");
          failed = true;
        }
      }
    }
    turnOff(i);
  }
  allOff();
  if(failed) flashRed();
  Serial.println(" Done.");
}

void testContinuity() {
  Serial.println(" Testing Continuity...");
  bool failed = false;
  bool is10Pin = true;
  allOff();
  for(int i=0; i<8; i++) {
    turnOn(i);
    Serial.print("  Pins ");
    printPins(i);
    if(notConnected(i)) {
      if(i < 5) is10Pin = false;
      failed = true;
      Serial.println(" FAILED!");
    } else {
      if(i >=5) is10Pin = false;
      Serial.println(" passed.");
    }
    turnOff(i);
  }
  allOff();
  if(failed) {
    if(is10Pin) flashGreen();
    solidRed();
  }
  Serial.println(" Done.");
}

void loop() {}

void solidGreen() {
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(12,LOW);
  while(true) {
    digitalWrite(11,HIGH);
    delay(1);
    digitalWrite(11,LOW);
    delay(7);
  }
}

void doubleFlash() {
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(12,LOW);
  while(true) {
    for(int i=0; i<31; i++) {
      digitalWrite(11,HIGH);
      delay(1);
      digitalWrite(11,LOW);
      delay(7);
    }
    for(int i=0; i<31; i++) {
      digitalWrite(12,HIGH);
      delay(1);
      digitalWrite(12,LOW);
      delay(7);
    }
  }
}

void flashGreen() {
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(12,LOW);
  while(true) {
    for(int i=0; i<31; i++) {
      digitalWrite(11,HIGH);
      delay(1);
      digitalWrite(11,LOW);
      delay(7);
    }
    delay(250);
  }
}

void solidRed() {
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(12,HIGH);
  while(true) {
    digitalWrite(11,LOW);
    delay(1);
    digitalWrite(11,HIGH);
    delay(7);
  }
}

void flashRed() {
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  while(true) {
    for(int i=0; i<31; i++) {
      digitalWrite(12,HIGH);
      delay(1);
      digitalWrite(12,LOW);
      delay(7);
    }
    delay(250);
  }
}
