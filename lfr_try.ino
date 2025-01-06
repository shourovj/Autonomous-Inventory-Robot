int pin = 13;
// For 4 wheels -> en1,en2,in1,in2,in3,in4 
int stp = 3;
int flag;
int flag_input;
int f = 0;
int r_en1 = 12;
int l_en1  = 9;
int rpwm1 = 11;
int lpwm1 = 10;
int r_en2=2;
int l_en2=3;  
int rpwm2=5;
int lpwm2=6;
int out1 = A1;

int out2 =A2;
int out3 =A3;
int out4 =A4;
int out5 =A5;
int speed=20;

int blackThreshold=750;

long timeInMicro;
long distanceInCm;

  // put your main code here, to run repeatedly:
int sensor1Value;
int sensor2Value;
int sensor3Value;
int sensor4Value;
int sensor5Value;

int s1, s2, s3, s4, s5;
int state; // moving = 1, stop = 0

void moveForward()
{
  
  analogWrite(rpwm1,speed);
  analogWrite(rpwm2,0);
  analogWrite(lpwm1,0);
  analogWrite(lpwm2,speed);

}

void moveBackward()
{
  
  analogWrite(rpwm1,0);
  analogWrite(rpwm2,speed);
  analogWrite(lpwm1,speed);
  analogWrite(lpwm2,0);
}

void turnLeft()
{
  analogWrite(rpwm1,0);
  analogWrite(rpwm2,0);
  analogWrite(lpwm1,speed);
  analogWrite(lpwm2,speed);
  delay(80);

}

void turnRight()
{ 
  analogWrite(rpwm1,speed);
  analogWrite(rpwm2,speed);
  analogWrite(lpwm1,0);
  analogWrite(lpwm2,0);
  delay(80);
}

void stop()
{ 
  analogWrite(rpwm1,0);
  analogWrite(rpwm2,0);
  analogWrite(lpwm1,0);
  analogWrite(lpwm2,0);
}

void convert_digital()
{
  s1 = 0;
  s2 = 0;
  s3 = 0;
  s4 = 0;
  s5 = 0;
  if(sensor2Value > blackThreshold) s2 = 1;
  if(sensor4Value > blackThreshold) s4 = 1;
  if(sensor3Value > blackThreshold) s3 = 1;
  if(sensor5Value > blackThreshold) s5 = 1;
  if(sensor1Value > blackThreshold) s1 = 1;
}


void setup() {
  // put your setup code here, to run once:

  pinMode(pin, OUTPUT);
  pinMode(l_en1, OUTPUT);
  pinMode(r_en1, OUTPUT);
  pinMode(l_en1, OUTPUT);
  pinMode(rpwm1, OUTPUT );
  pinMode(lpwm1, OUTPUT);
  pinMode(r_en2, OUTPUT);
  pinMode(l_en2, OUTPUT);
  pinMode(rpwm2, OUTPUT);
  pinMode(lpwm2, OUTPUT);
  digitalWrite(r_en1, HIGH);  
  digitalWrite(l_en1,HIGH);
  digitalWrite(r_en2,HIGH);
  digitalWrite(l_en2,HIGH);
  Serial.begin(9600);
  analogWrite(rpwm1,0);
  analogWrite(rpwm2,0);
  analogWrite(lpwm1,0);
  analogWrite(lpwm2,0);

  state = 1;
 
}

void loop() {
  moveForward();

if (Serial.available()) {  // Check if data is available to read
  String command = Serial.readString();  // Read the incoming data
  if (command == "HIGH") {
    digitalWrite(13, HIGH); // Turn the LED on
    delay(1000);            // Wait for 1 second
    digitalWrite(13, LOW);  // Turn the LED off
    delay(1000); 
    Serial.println("Pin set to HIGH");
  } else {
    Serial.println("Unknown command");
  }
}

if(digitalRead(pin)==HIGH){
  Serial.print("Paichi");
}

  // put your main code here, to run repeatedly:
sensor1Value = analogRead(A1);
sensor2Value = analogRead(A2);
sensor3Value = analogRead(A3);
sensor4Value = analogRead(A4);
sensor5Value = analogRead(A5);
  
convert_digital();


Serial.println("----");
Serial.print(sensor1Value);
Serial.print("----");
Serial.print(sensor2Value);
Serial.print("----");
Serial.print(sensor3Value);
Serial.print("----");
Serial.print(sensor4Value);
Serial.print("----");
Serial.print(sensor5Value);
Serial.println("----");
Serial.print(s1);
Serial.print("-");
Serial.print(s2);
Serial.print("-");
Serial.print(s3);
Serial.print("-");
Serial.print(s4);
Serial.print("-");
Serial.println(s5);
delay(300);
Serial.println(stp);

//------------------------
flag_input = Serial.parseInt();
if(!stp)
{
  moveBackward();
  delay(30000);
}

if (state)
{
  if((s1==0)&&(s2==0)&&(s3==0)&&(s4==0)&&(s5==0)) //stopage detection, state = 1
  {
    state = 1 - state;
    stop();
    delay(5000);
    stp--;
    Serial.println("---");
    Serial.print(stp);
  }
}
else //state = 0
{
  
  if((s1==1)&&(s2==1)&&(s3==0)&&(s4==1)&&(s5==1))
  {
    state = 1 - state;
    moveForward();

  }
  else if((s1==1)&&(s2==1)&&(s3==0)&&(s4==1)&&(s5==1))
  {
    
  }
}

}