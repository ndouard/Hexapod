#include "Servo.h"

Servo mot[6][3];
int offset[6][3];
int md; // delay between 'movements'

// US definition
const int trigPin = 15;
const int echoPin = 14;

void setup() {
  Serial.begin (9600); 
  //US
  pinMode(trigPin, OUTPUT);  // trig is an output
  pinMode(echoPin, INPUT);   // echo is an input
  
  md = 200; // delay between 'movements'
  
  mot[0][0].attach(46);
  mot[0][1].attach(4);
  mot[0][2].attach(26);

  offset[0][0] = 0;
  offset[0][1] = 1;
  offset[0][2] = 2;
  
  
  mot[1][0].attach(48);
  mot[1][1].attach(5);
  mot[1][2].attach(32);

  offset[1][0] = 0;
  offset[1][1] = 14;
  offset[1][2] = 7;
  
  mot[2][0].attach(50);
  mot[2][1].attach(6);
  mot[2][2].attach(34);

  offset[2][0] = 0;
  offset[2][1] = 0;
  offset[2][2] = 9;
  
  mot[3][0].attach(52);
  mot[3][1].attach(7);
  mot[3][2].attach(36);

  offset[3][0] = 0;
  offset[3][1] = 12;
  offset[3][2] = 3;

  mot[4][0].attach(42);
  mot[4][1].attach(2);
  mot[4][2].attach(22);

  offset[4][0] = 0;
  offset[4][1] = 10;
  offset[4][2] = 7;
  
  mot[5][0].attach(44);
  mot[5][1].attach(3);
  mot[5][2].attach(24);

  offset[5][0] = 0;
  offset[5][1] = 1;
  offset[5][2] = 0;
}


void loop() {
  // check distance
  if (getUS() > 35.0f){
	// move 'forward' if object not in front
	// moveFwd() is very quick to execute once so doing
	// it w/o interrupts or using millis() works properly
	// few centimeters per moveFwd() call
	moveFwd();
	delay(100);
  }
  else{
	// default steady position
	resetPos();
	delay(100);
	// rotate until not facin obstacle 
	// few degrees per Rotate() call
	rotate();
  }
}



float getUS() {
  long duration;
  float distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // trig 10ms HIGH
  digitalWrite(trigPin, LOW);
 
  // echo calculation
  duration = pulseIn(echoPin, HIGH);
  // distance proportional to the output duration
  distance = duration*340/(2*10000);  // sound speed
  
  // out of range
  if ( distance <= 0){ 
	Serial.println("Out of range");
  }
  else {
	Serial.print(distance);
	Serial.print(" cm ");
	Serial.print(duration);
	Serial.println(" ms");
	return(distance);
  }
}

// default steady position
void resetPos(){
  for (int i=0; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+34);
	mot[i][2].write(offset[i][2]+40);
  }
  delay(md);

}

// not used - kept for future additions
void nicePose(){
	 for (int i=1; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+100);
	mot[i][2].write(offset[i][2]+110);
  }
}

// not used - kept for future additions
void fwdPose(){
  for (int i=1; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+34);
	mot[i][2].write(offset[i][2]+40);
  }
}


// rotates on itself
// few degrees per Rotate() call
void rotate(){
   Serial.write("Rotate"); // avoids obstacle, rotates on itself 
   
   mot[0][2].write(45);
   mot[2][2].write(45);
   mot[4][2].write(45); // leg low
   mot[0][1].write(150);
   mot[2][1].write(150); // middle leg
   mot[4][1].write(150); // 3 first legs up and done
 
   delay(500);
   mot[0][0].write(0);
   mot[2][0].write(0);
   mot[4][0].write(0);// core rotation and done

   delay(500);
   
   mot[0][2].write(135);
   mot[2][2].write(135);
   mot[4][2].write(135);
   mot[0][1].write(30);
   mot[2][1].write(30);
   mot[4][1].write(30);// lower 3 first legs
   
   delay(500);
   mot[1][2].write(45);
   mot[4][2].write(45);
   mot[5][2].write(45);
   mot[1][1].write(150);
   mot[3][1].write(150);
   mot[5][1].write(150);// raise 3 next legs
   
   delay(500);
   mot[1][0].write(0);
   mot[3][0].write(0);
   mot[4][0].write(0);// 2nd rotation
   
   
   delay(500);
   mot[1][2].write(135);
   mot[3][2].write(135);
   mot[5][2].write(135);
   mot[1][1].write(30);
   mot[3][1].write(30);
   mot[5][1].write(30);
   delay(500); // lower legs

   mot[0][0].write(90);
   mot[1][0].write(90);
   mot[2][0].write(90);
   mot[3][0].write(90);
   mot[4][0].write(90);
   mot[5][0].write(90); // final rotation and end
}


// move straight forward
void moveFwd(){
	for (int i=0; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+34);
	mot[i][2].write(offset[i][2]+40);
  }
  delay(md);

   for (int i=1; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+100);
	mot[i][2].write(offset[i][2]+110);
  }
  delay(md);
  dir1();
  delay(md);

  for (int i=1; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+34);
	mot[i][2].write(offset[i][2]+40);
  }
  delay(md);
  for (int i=1; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+100);
	mot[i][2].write(offset[i][2]+110);
  }
  delay(md);
  dir2();
  delay(md);
  for (int i=1; i<6; i+=2)
  {
	mot[i][0].write(90);
	mot[i][1].write(offset[i][1]+34);
	mot[i][2].write(offset[i][2]+40);
  }
  delay(md);
  
}

// used in 'moveFwd' as pose - legs slight rotation
void dir1(){
  // full
   for (int i=0; i<6; i+=1)
	{
	  mot[i][0].write(60);
	}
   // 'special'
   for (int i=0; i<6; i+=2)
	{
	  mot[i][0].write(120);
	}
}

// used in 'moveFwd' as pose
// legs slight rotation in opposite direction relative to dir1()
void dir2(){
  // full opposite
   for (int i=0; i<6; i+=1)
	{
	  mot[i][0].write(120);
	}
   // 'special' opposite
   for (int i=0; i<6; i+=2)
	{
	  mot[i][0].write(60);
	}
}