#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
template <typename T_ty> struct TypeInfo { static const char * name; };
template <typename T_ty> const char * TypeInfo<T_ty>::name = "unknown";
RTC_DS1307 rtc;
String zero = "0";
String dash = "-";
String twelve = "12";
bool table[10][4] = {
  // D, C, B, A , white blue green yellow wire color
  {0, 0, 0, 0}, // 0
  {1, 0, 0, 0}, // 1
  {0, 1, 0, 0}, // 2
  {1, 1, 0, 0}, // 3
  {0, 0, 1, 0}, // 4
  {1, 0, 1, 0}, // 5
  {0, 1, 1, 0}, // 6
  {1, 1, 1, 0}, // 7
  {0, 0, 0, 1}, // 8
  {1, 0, 0, 1}, // 9
};
int tubeConnections[6][4] = {
  {25, 27, 29, 31},
  {24, 26, 28, 30},
  {34, 36, 38, 40},
  {35, 37, 39, 41},
  {44, 46, 48, 50},
  {45, 47, 49, 51}
};
void showOnTube(int tube, int num) {
  int a = 1, b = 1, c = 1, d = 1; // a,b,c,d all one = tube off.
  if (num >= 0) {
    a = table[num][3];
    b = table[num][2];
    c = table[num][1];
    d = table[num][0];
  }
  digitalWrite(tubeConnections[tube][0], a);
  digitalWrite(tubeConnections[tube][1], b);
  digitalWrite(tubeConnections[tube][2], c);
  digitalWrite(tubeConnections[tube][3], d);
  delay(5);
}
void tubeDisplay(String num) {
  String numberString = String(num);
  int length = numberString.length();
  switch (length) {
    case 0: return;
    case 1: numberString = "     " + numberString; break;
    case 2: numberString = "    " + numberString; break;
    case 3: numberString = "   " + numberString; break;
    case 4: numberString = "  " + numberString; break;
    case 5: numberString = " " + numberString; break;
    case 6: break;
    default: return;
  }
  for (int i = 0; i < 6 ; i++) {
    //Serial.print((int)numberString.charAt(i)-48); Serial.print(" ");
    showOnTube(i, (int)numberString.charAt(5 - i) - 48);
  }
  //Serial.println();
}
void setup() {
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);

  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(31, OUTPUT);

  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(40, OUTPUT);

  pinMode(35, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(41, OUTPUT);

  pinMode(44, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(50, OUTPUT);

  pinMode(45, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(51, OUTPUT);  

  // RTC
  pinMode(18, OUTPUT); digitalWrite(18, LOW);
  pinMode(19, OUTPUT); digitalWrite(19, HIGH);
  Serial.begin(57600);
  Wire.begin();
  rtc.begin();
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    
  }
  //uncomment line to set RTC to compile datetime
  //rtc.adjust(DateTime(__DATE__, __TIME__));
  Serial.println("Initialization.");
  Serial.println(__TIME__);
}
void loop() {
  // grab the time from the RTC
  DateTime now = rtc.now();

  // format the hour as 12-hour format (without this, 24-h format)
  int hr = now.hour() > 12 ? now.hour() - 12 : now.hour();
  if(hr==0) hr = 12;

  // pad with zero if less than 10
  String theHour = hr < 10 ? zero + String(hr) : String(hr);

  // pad with zero if less than 10
  int mint = now.minute();
  mint = mint < 0 ? 0 : mint; // ensure greater than zero
  String theMin  = mint < 10 ? zero + String(mint) : String(mint);

  int date = now.day();
  String theDay  = date < 10 ? zero + String(date) : String(date);
  
  // show on the tubes
  tubeDisplay(theDay + theHour + theMin); //Serial.println(theHour + theMin);

  // ensure all nums light up at 6|9:01am and pm.
  if ((hr == 6 || hr == 9) && mint == 1) degauss(20000); 
  
  delay(250);

  /*Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(now.second(), DEC);*/
}

void degauss(int degauss_time) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 6; j++) {
      showOnTube(j, i);
    }
    delay(degauss_time); // wait 20 secs
  }
}

