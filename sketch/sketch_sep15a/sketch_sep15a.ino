void setup() {
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  while(Serial.available()) {
    String a = Serial.readString();
    char f = a[0];
    int test = (int) f - 48;
    //Serial.println("hello");
    a.remove(0, 2);
    switch(test){
      case 0:
        Serial.print("Recieved on RS485: " + a);
        break;
      case 1:
        Serial.print("Recieved on CAN: " + a);
        break;
      default:
        Serial.print("Unknow interface\n");
        break;
    }
  }
}
