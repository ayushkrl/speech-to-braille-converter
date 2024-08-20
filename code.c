#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


byte myBrailleDots[255];
int buzzerPin = A0; // Buzzer on pin 8
byte matrixPoints = 0; // byte that will store the point  matrix configuration for a specific ASCII character
byte inByte;
byte mask = 1; //our bitmask

int dot1=2;
int dot2=3;
int dot3=4;
int dot4=5;
int dot5=6;
int dot6=7;
Servo sn[6];//servoNumber

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  sn[0].attach(dot1);
  sn[1].attach(dot2);
  sn[2].attach(dot3);
  sn[3].attach(dot4);
  sn[4].attach(dot5);
  sn[5].attach(dot6);


  for (int i = 0; i < 256; i =  i + 1) {
     myBrailleDots[i] = 99;
  }

  // Now, only for the ASCII  characters with a corresponding Braille character.
  // assign the corresponding  Braille Dot configuration
  myBrailleDots[32] = 0;  // blank is 000000
  myBrailleDots[33]  = 14;  // exlamation mark is 001110
  myBrailleDots[34] = 7;  // double quote  is 000111
  myBrailleDots[34] = 2;  // single quote is 000010
  myBrailleDots[40]  = 15;  // left parenthesis is 001111
  myBrailleDots[41] = 15;  // right parenthesis  is 001111
  myBrailleDots[44] = 8;  // comma is 001000
  myBrailleDots[46]  = 13;  // period is 001101
  myBrailleDots[48] = 28; // 0 is 011100
  myBrailleDots[49]  = 32; // 1 is 100000
  myBrailleDots[50] = 40; // 2 is 101000
  myBrailleDots[51]  = 48; // 3 is 110000
  myBrailleDots[52] = 52; // 4 is 110100
  myBrailleDots[53]  = 36; // 5 is 100100
  myBrailleDots[54] = 56; // 6 is 111000
  myBrailleDots[55]  = 60; // 7 is 111100
  myBrailleDots[56] = 44; // 8 is 101100
  myBrailleDots[57]  = 24; // 9 is 011000
  myBrailleDots[58] = 12; // colon is 001100
  myBrailleDots[59]  = 10; // semicolon is 001010
  myBrailleDots[63] = 11; // question mark is 001011
  myBrailleDots[65] = 32; // A is 100000
  myBrailleDots[66] = 40; // B is 101000
  myBrailleDots[67] = 48; // C is 110000
  myBrailleDots[68] = 52; // D is 110100
  myBrailleDots[69] = 36; // E is 100100
  myBrailleDots[70] = 56; // F is 111000
  myBrailleDots[71] = 60; // G is 111100
  myBrailleDots[72] = 44; // H is 101100
  myBrailleDots[73] = 24; // I is 011000
  myBrailleDots[74] = 28; // J is 011100
  myBrailleDots[75] = 34; // K is 100010
  myBrailleDots[76] = 42; // L is 101010
  myBrailleDots[77] = 50; // M is 110010
  myBrailleDots[78] = 54; // N is 110110
  myBrailleDots[79] = 38; // O is 100110
  myBrailleDots[80] = 58; // P is 111010
  myBrailleDots[81] = 62; // Q is 111110
  myBrailleDots[82] = 46; // R is 101110
  myBrailleDots[83] = 26; // S is 011010
  myBrailleDots[84] = 30; // T is 011110
  myBrailleDots[85] = 35; // U is 100011
  myBrailleDots[86] = 43; // V is 101011
  myBrailleDots[87] = 29; // W is 011101
  myBrailleDots[88] = 51; // X is 110011
  myBrailleDots[89] = 55; // Y is 110111
  myBrailleDots[90] = 39; // Z is 100111
  myBrailleDots[97] = 32; // A is 100000
  myBrailleDots[98] = 40; // B is 101000
  myBrailleDots[99] = 48; // C is 110000
  myBrailleDots[100] = 52; // D is 110100
  myBrailleDots[101] = 36; // E is 100100
  myBrailleDots[102] = 56; // F is  111000
  myBrailleDots[103] = 60; // G is 111100
  myBrailleDots[104] = 44;  // H is 101100
  myBrailleDots[105] = 24; // I is 011000
  myBrailleDots[106]  = 28; // J is 011100
  myBrailleDots[107] = 34; // K is 100010
  myBrailleDots[108]  = 42; // L is 101010
  myBrailleDots[109] = 50; // M is 110010
  myBrailleDots[110]  = 54; // N is 110110
  myBrailleDots[111] = 38; // O is 100110
  myBrailleDots[112]  = 58; // P is 111010
  myBrailleDots[113] = 62; // Q is 111110
  myBrailleDots[114]  = 46; // R is 101110
  myBrailleDots[115] = 26; // S is 011010
  myBrailleDots[116]  = 30; // T is 011110
  myBrailleDots[117] = 35; // U is 100011
  myBrailleDots[118]  = 43; // V is 101011
  myBrailleDots[119] = 29; // W is 011101
  myBrailleDots[120]  = 51; // X is 110011
  myBrailleDots[121] = 55; // Y is 110111
  myBrailleDots[122]  = 39; // Z is 100111

  // pinMode(buzzerPin, OUTPUT); //if un-translatable character come pin 8 will buzz
  // dot1.attach(2);
  // dot2.attach(3);
  // dot3.attach(4);
  // dot4.attach(5);
  // dot5.attach(6);
  // dot6.attach(7);

  Serial.println("ASCII  - Braille Arduino Converter"); //Print on serial monitor
  Serial.println("servoTest - begin");                   //when arduino start displaying the character it will print
  sn[0].write(90);                                 
  sn[1].write(90);
  sn[2].write(90);
  sn[3].write(90);
  sn[4].write(90);
  sn[5].write(90);
  delay(1000);
  sn[0].write(0);                                 
  sn[1].write(0);
  sn[2].write(0);
  sn[3].write(0);
  sn[4].write(0);
  sn[5].write(0);
  Serial.println("servoTest - end");
  Serial.println("Type  some character: it will be transmitted to Arduino and displayed on a Braille 2 x 3 matrix");
}

void loop() {
    if (Serial.available() > 0) {
      // read the incoming  byte:
      inByte = Serial.read();
      // say what you got:
      Serial.print("Received  (inByte): ");
      Serial.println(inByte);
      // Translate inByte in  matrix points
      Serial.print("Matrix points variable (myBrailleDots[inByte]):  ");
      Serial.println(myBrailleDots[inByte]);

      if (myBrailleDots[inByte] == 99) {
        sn[0].write(0);
        sn[1].write(0);
        sn[2].write(0);
        sn[3].write(0);
        sn[4].write(0);
        sn[5].write(0);
        Serial.println("Not  a translatable character");
        analogWrite(buzzerPin,128); // buzz
        delay(1000); 
        analogWrite(buzzerPin,LOW); // stop buzzing
    }
    else {
      // sn[0].write(90);  // Set servo angle for dot 1
      // sn[1].write(90);  // Set servo angle for dot 2
      // sn[2].write(90);  // Set servo angle for dot 3
      // sn[3].write(90);  // Set servo angle for dot 4
      // sn[4].write(90);  // Set servo angle for dot 5
      // sn[5].write(90);  // Set servo angle for dot 6
      char character = char(inByte);
      lcd.print(character);
      int thisPin = 2;
      for (mask  = 000001; mask<64; mask <<= 1) { 
          Serial.print("thisPin =  ");
          Serial.println(thisPin); 
          if (myBrailleDots[inByte]  & mask){ // if bitwise AND resolves to true
              Serial.print("AND  successful, put pin on!");
              Serial.println(mask);  
              sn[thisPin-2].write(90);
                           
              }
          else{ //if bitwise and resolves to false
              Serial.print("AND  unsuccessful, put pin off!");
              Serial.println(mask);  
              sn[thisPin-2].write(0);
          }
      thisPin  = thisPin + 1;   
      }
    }

    delay(1000); // allow  1 sec before passing to next character
  }
}