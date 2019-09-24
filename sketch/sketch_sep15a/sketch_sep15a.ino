int arr[5];
void setup() {
  Serial.begin(9600);
  Serial.flush();

}

void loop() {
  while(Serial.available()) {
    String a = Serial.readString();
    if (a.length() == a[1]) {
      Serial.write(1);
    } else {
      Serial.write(0);
    }
  }
}
