int pin=4;
int ir1 = A0;
int c = 0;
int ir2 = A1;
unsigned long value = 0;
void setup() {
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(pin, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}
void forward() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void left() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
void right() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void stop() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
long st = millis(), endt;
int flag = 0;

void loop() {
    if ( Serial.read() == 'X' || flag == 1 ){
      if(digitalRead(pin) > 0){
        value=pulseIn(pin,HIGH);
        Serial.println("value=");
        Serial.println(value);

        if(value>1500 && value < 2000){
          Serial.println("Gantry one crossed");
          stop();
          delay(1000);
        }
        if(value>2500 && value < 3000){
          Serial.println("Gantry two crossed");
          stop();
          delay(1000);
        }
        if(value> 500 && value < 1000){
          Serial.println("Gantry three crossed");
          stop();
          delay(1000);
          }
        }
      flag = 1;

    int l = digitalRead(ir1);
    int r = digitalRead(ir2);
   
    if (l == 1 && r == 1) forward();
    if (l == 1 && r == 0) right();
    if (l == 0 && r == 1) left();
    if (l == 0 && r == 0){
      endt = millis();
      if (endt - st > 1000) {
        c++;
        st = millis();
      }
      if (c == 1 || c == 3 || c == 4) {
        forward();
        Serial.print("Forward ");
        Serial.println(c);
      }
      else if (c == 5) {
        right();
        delay(500);
        Serial.print("right \n");
        Serial.println(c);
      }
      else if (c == 2) {
        right();
        delay(500);
        Serial.print("right \n");
        Serial.println(c);
      }
      else if (c == 6) {
        forward();
        Serial.print("Forward \n");
        Serial.println(c);
      }
      else if (c > 6) {
        stop();
        Serial.print("Stop");
        Serial.println(c);
        flag = 0;
      }
    }
  }
}
