bool table[10][4] = {
  // D, C, B, A
  {0, 0, 0, 0}, // 0
  {0, 0, 0, 1}, // 1
  {0, 0, 1, 0}, // 2
  {0, 0, 1, 1}, // 3
  {0, 1, 0, 0}, // 4
  {0, 1, 0, 1}, // 5
  {0, 1, 1, 0}, // 6
  {0, 1, 1, 1}, // 7
  {1, 0, 0, 0}, // 8
  {1, 0, 0, 1}, // 9
};
void display(int tube, int num) {
  int a = 0, b = 0, c = 0, d = 0; // a,b,c,d all zero
  digitalWrite(2, a);
  digitalWrite(3, b);
  digitalWrite(4, c);
  digitalWrite(5, d);
  delay(2);
  a = table[num][3];
  b = table[num][2];
  c = table[num][1];
  d = table[num][0];
  delay(2);
  digitalWrite(2, a);
  digitalWrite(3, b);
  digitalWrite(4, c);
  digitalWrite(5, d);
}
void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
}
void loop() {
    for(int i=0; i<10; i++) {
        display(1, i);
        delay(350);
    }
}
