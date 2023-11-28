void outputaddress(unsigned int);
byte readbyte();
void setup() {
  byte data;
  char outstr[256];
  byte cksum;
  unsigned int byteaddr = 0;

  // Set up address pins as outputs address bit A0 - A11
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);

  pinMode(41, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(38, OUTPUT);

  // Digital pins default to inputs but just in case data bit D0 - D7
  pinMode(49, INPUT);
  pinMode(48, INPUT);
  pinMode(47, INPUT);
  pinMode(46, INPUT);
  pinMode(45, INPUT);
  pinMode(44, INPUT);
  pinMode(43, INPUT);
  pinMode(42, INPUT);

  Serial.begin(9600);
  Serial.println();
  Serial.println("Start");
  Serial.println();

  // Output data in Intel hex format based at 0000

  for (byteaddr = 0; byteaddr < 4096; byteaddr++) {
    if ((byteaddr % 16) == 0) {
      sprintf(outstr, ":10%04X00", byteaddr);
      Serial.print(outstr);
      cksum = 0x10 + (byteaddr >> 8) + (byteaddr & 0xFF) + 0x00;
    }
    // read the EPROM
    outputaddress(byteaddr);
    delay(1);
    data = readbyte();
    cksum += data;

    // output this byte
    sprintf(outstr, "%02X", data);
    Serial.print(outstr);
    // end of line
    if (((byteaddr + 1) % 16) == 0) {
      sprintf(outstr, "%02X", (byte)((~cksum) + 1));
      Serial.println(outstr);
    }
  }
  // eof
  Serial.println(":00000001FF");
}

void loop() {
  // put your main code here, to run repeatedly:
}

void outputaddress(unsigned int addr) {

  if (addr & 0x0001) digitalWrite(22, 1);
  else digitalWrite(22, 0);
  if (addr & 0x0002) digitalWrite(23, 1);
  else digitalWrite(23, 0);
  if (addr & 0x0004) digitalWrite(24, 1);
  else digitalWrite(24, 0);
  if (addr & 0x0008) digitalWrite(25, 1);
  else digitalWrite(25, 0);
  if (addr & 0x0010) digitalWrite(26, 1);
  else digitalWrite(26, 0);
  if (addr & 0x0020) digitalWrite(27, 1);
  else digitalWrite(27, 0);
  if (addr & 0x0040) digitalWrite(28, 1);
  else digitalWrite(28, 0);
  if (addr & 0x0080) digitalWrite(29, 1);
  else digitalWrite(29, 0);

  if (addr & 0x0100) digitalWrite(41, 1);
  else digitalWrite(41, 0);
  if (addr & 0x0200) digitalWrite(40, 1);
  else digitalWrite(40, 0);
  if (addr & 0x0400) digitalWrite(39, 1);
  else digitalWrite(39, 0);
  if (addr & 0x0800) digitalWrite(38, 1);
  else digitalWrite(38, 0);
}

byte readbyte() {
  byte data = 0;
  if (digitalRead(49)) data |= 0x01;
  if (digitalRead(48)) data |= 0x02;
  if (digitalRead(47)) data |= 0x04;
  if (digitalRead(46)) data |= 0x08;
  if (digitalRead(45)) data |= 0x10;
  if (digitalRead(44)) data |= 0x20;
  if (digitalRead(43)) data |= 0x40;
  if (digitalRead(42)) data |= 0x80;
  return data;
}