void setup() {
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  while(Serial.available()) {
    String a = Serial.readString();
    int interface = a[0];
    int sum = a[1];
    a.remove(0,2);
    if (a.length() == sum) {
      switch (interface) {
        case 1:
          Serial.write(1);
          break;
        case 2:
          Serial.write(2);
          break;
        case 3:
          Serial.write(3);
          break;
        default:
          Serial.write(0);
          break;
      }
    } else {
      Serial.write(0);
    }
  }
}
