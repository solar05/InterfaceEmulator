
#include <uCRC16BPBLib.h>
 
char test[5];
 
void setup() {
  Serial.begin(9600);
  Serial.flush();
  test[0] = '\x01';
  test[1] = 't';
  test[2] = 'e';
  test[3] = 's';
  test[4] = 't';
}
 
 
uCRC16BPBLib crc;
 
uint16_t crcStringBytes(char * string, uint16_t length) {
  uint16_t i;
  crc.reset();
  for (i = length; i > 0; string++, i--) {
    crc.feedByte(*string);
  }
  return crc.getResult();
}
 
void loop() {
  uint16_t crc;
  Serial.print(crcStringBytes(test,5));
  Serial.print("\n");
  delay(2000);
}
