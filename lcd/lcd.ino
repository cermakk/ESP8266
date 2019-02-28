#define CLK 10
#define DATA 11
#define CS 12

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Zobovo display\n=============");

  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CS, OUTPUT);

  digitalWrite(DATA, LOW);
  digitalWrite(CLK, LOW);
  digitalWrite(CS, HIGH);

  delay(20);
  //po zapnuti napajeni se ma pockat 20ms
}


void send_to_disp(unsigned char _vstupni_data, unsigned char _rs)
{
  volatile unsigned char i=0;
  volatile unsigned long poskladane_dato=0xf8;
  _rs<<=1;
  poskladane_dato|=_rs;
  poskladane_dato<<=1;

  for(; i<4; i++)
  {
      poskladane_dato|=(_vstupni_data&0x01);
      _vstupni_data>>=1;
      poskladane_dato<<=1;
    }
  poskladane_dato<<=4;
  for(i=0; i<4; i++)
  {
      poskladane_dato|=(_vstupni_data&0x01);
      _vstupni_data>>=1;
      poskladane_dato<<=1;
    }
  poskladane_dato<<=3;

  Serial.print("Poskladana data: ");
  Serial.println(poskladane_dato, BIN);

  Serial.print("Posilam: ");
  digitalWrite(CS, LOW);
  delay(10);
  for(i=0; i<24; i++)
  {
      if( (poskladane_dato&0x00800000) > 0) digitalWrite(DATA, HIGH); else digitalWrite(DATA, LOW);
      delay(1);
      digitalWrite(CLK, HIGH); delay(1); digitalWrite(CLK, LOW); delay(1);
      poskladane_dato<<=1;
      
      Serial.print(digitalRead(DATA));
      Serial.print(" ");
    }
  digitalWrite(CS, HIGH);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

  //lcd init
  send_to_disp(0x38, 0); //8bit mode, 2 lines
  delay(1);
  send_to_disp(0x0C, 0); //display on, cursor off, blink off
  delay(1);
  send_to_disp(0x01, 0); //clear display
  delay(2);
  send_to_disp(0x06, 0); //increment mode, no shift
  delay(10);

  //lcd write text
  send_to_disp('A', 1);
  delay(1);
  send_to_disp('h', 1);
  delay(1);
  send_to_disp('o', 1);
  delay(1);
  send_to_disp('j', 1);
  delay(1);


 
  while(1);

}
