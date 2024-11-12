int command;

int Speed = 0;
int Stop = 0;
int Normal = 150;           //normal speed
int Slowed = Normal - 50;   //slowed speed
int Humidity = 0;

#define SENSOR 7
#define VALUE A5

#define LMF 12
#define LMB 13
#define RMF 11
#define RMB 10

void setup() {
  // put your setup code here, to run once:
pinMode(LMF, OUTPUT);   //left motors forward
pinMode(LMB, OUTPUT);   //left motors backward
pinMode(RMF, OUTPUT);   //right motors forward
pinMode(RMB, OUTPUT);   //right motors backward
Serial.begin(9600);

pinMode(SENSOR, OUTPUT);
digitalWrite(SENSOR, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(SENSOR, HIGH);
delay(30);
Humidity = analogRead(VALUE);
digitalWrite(SENSOR, LOW);

Serial.println(Humidity);

if (Speed >= 50) {
  if (Humidity >= 150) {    //change later
    Speed = Slowed;
  }
  else if (Humidity < 150) {
    Speed = Normal;
  }
  analogWrite(LMF, Speed);
  analogWrite(RMF, Speed);
}

if (Serial.available() > 0) {
  command = Serial.read();
  Serial.println(command);
}
if (command == 'X') {
  Speed = Normal;
  analogWrite(LMF, Speed);
  analogWrite(RMF, Speed);    //change back
}
if(command == 'Y') {
  Speed = Stop;
  analogWrite(LMF, Speed);
  analogWrite(RMF, Speed);
}
delay(1000);
}