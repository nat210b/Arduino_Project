//18_วรรณชล
int stats = 0;
int stats1 = 0;

void setup() {

  for (int i = 2 ; i <= 9 ; i++ ) {
    pinMode(i, OUTPUT);
  }
  pinMode(14, INPUT);
  pinMode(15, INPUT);
}


void loop() {
  //------------------------------
  if (digitalRead(14) == 0) {
    delay(10);
    if (digitalRead(14) == 1) {
      stats = 1;
      stats1 = 0;
    }
  }
  //**
  if (digitalRead(15) == 0) {
    delay(10);
    if (digitalRead(15) == 1) {
      stats1 = 1;
      stats = 0;
    }
  }

  //-------------------------------
  if (stats == 1) {
    for (int i = 9; i >= 2 ; i--) { 
      digitalWrite(i, 1);
      delay(500);
      digitalWrite(i, 0);
    }
    
  }
 
  //**
  if (stats1 == 1) {
    for (int i = 2; i <= 9 ; i++) {
      digitalWrite(i, 1);
      delay(500);
      digitalWrite(i, 0);
    }
  }
}
