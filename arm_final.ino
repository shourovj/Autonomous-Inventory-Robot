#include <Servo.h> // Include the Servo library
 
Servo Servo1; // Create a Servo object
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;
Servo Servo7;

const int pin13 = 13;
void setup() {
  pinMode(pin13, OUTPUT);
  Servo1.attach(2); // Attach the servo to pin 9
  Servo2.attach(3);
  Servo3.attach(4);
  Servo4.attach(5);
  Servo5.attach(6);
  Servo6.attach(7);
 
  Serial.begin(9600); // Start Serial communication
  Serial.println("Servo Arm Control Initialized");
 
  // Move to stretched position
  Serial.println("Moving to stretched position...");
  //myServo.write(0); // 0 degrees (stretched)
  delay(2000); // Hold stretched position for 2 seconds
 
  // Move to hold position
  Serial.println("Moving to hold position...");
  //myServo.write(180); // 90 degrees (holding position)
  Servo2.write(150);
  delay(2000); // Hold the object
}
 
void claw_open()
{
  Servo1.write(0);
}
 
 
void claw_close()
{
  Servo1.write(50);
}
 
 
void servo2()
{
  Servo2.write(50);
}
 
void servo3()
{
  Servo3.write(140);
}
 
void servo4()
{
  Servo4.write(130);
}
 
void up()
{
  Servo5.write(140);
}
void down()
{
  Servo5.write(40);
}
 
void front()
{
  Servo6.write(100);
}
 
void left()
{
  Servo6.write(180);
}
 
void initial()
{
    Servo5.write(140);
    delay(100);
    Servo4.write(130);
    delay(100);
    Servo3.write(50);
    delay(100);
}
int flag = 0;
void loop() {
  // Stop the servo (it remains in the last position)
  // You can add further code here if needed.

  digitalWrite(pin13,LOW);
  int d = 1000;
  int dd = 2000;
  digitalWrite(5,LOW);
  if(Serial.available()>0){
    String msg = Serial.readString();
    if(msg=="gotit"){
      digitalWrite(13,HIGH);
      delay(100);
      Servo6.write(100);
      delay(d);
      Servo3.write(140);
      delay(d);
      Servo1.write(0);
      delay(dd);
      Servo1.write(50);
      delay(d);
      Servo3.write(50);
      delay(d);
      Servo6.write(0);
      delay(dd);
      Servo3.write(140);
      delay(d);
      Servo1.write(0);
      delay(dd);
      Servo1.write(50);
      delay(d);
      delay(3000);
      digitalWrite(5,HIGH);
    }
  }
  
}
 