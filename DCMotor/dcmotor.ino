#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR34_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor4(4, MOTOR34_64KHZ); // create motor #2, 64KHz pwm
 
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motor1.setSpeed(255);     // set the speed to 200/255
  motor2.setSpeed(255);     // set the speed to 200/255
  motor3.setSpeed(255);     // set the speed to 200/255
  motor4.setSpeed(255);     // set the speed to 200/255
}
 
void loop() {
  Serial.println("1");
  motor1.run(FORWARD);      // turn it on going forward
  delay(1000);
  motor1.run(RELEASE);

  Serial.println("2");
  motor2.run(FORWARD);
  delay(1000);
  motor2.run(RELEASE);
  
  Serial.println("3");
  motor3.run(FORWARD);
  delay(1000);
  motor3.run(RELEASE);
  
  Serial.println("4");
  motor4.run(FORWARD);
  delay(1000);
  motor4.run(RELEASE);
}