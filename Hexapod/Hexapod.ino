#include "Servo.h"

Servo mot[6][3];

int offset[6][3];
int md;
bool done;

//US
const int trigPin = 15;
const int echoPin = 14;

void setup() {
  Serial.begin (9600); 

  //US
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  
  done = false;
  //initial 2000
  md = 200;
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


void loop2() {
  if (getUS() > 35.0f){
    //move 'forward'
    moveFwd();
    delay(100);
  }
  else{
    resetPos();
    delay(100);
    Rotate();
  }
}

void loop(){
  moveFwd();
}

float getUS() {
  long duration;
  float distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);
 
  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique
  
  //Hors de portée
  if ( distance <= 0){ 
    Serial.println("Hors de portee");
  }
  else {
    Serial.print(distance);
    Serial.print(" cm ");
    Serial.print(duration);
    Serial.println(" ms");
    return(distance);
  }
}

void resetPos(){
  for (int i=0; i<6; i+=2)
  {
    mot[i][0].write(90);
    mot[i][1].write(offset[i][1]+34);
    mot[i][2].write(offset[i][2]+40);
  }
  delay(md);

}

void dir1(){
  //full
   for (int i=0; i<6; i+=1)
    {
      mot[i][0].write(60);
    }
   //special
   for (int i=0; i<6; i+=2)
    {
      mot[i][0].write(120);
    }
}

void dir2(){
  //full opposite
   for (int i=0; i<6; i+=1)
    {
      mot[i][0].write(120);
    }
   //special opposite
   for (int i=0; i<6; i+=2)
    {
      mot[i][0].write(60);
    }
}

void nicePose(){
     for (int i=1; i<6; i+=2)
  {
    mot[i][0].write(90);
    mot[i][1].write(offset[i][1]+100);
    mot[i][2].write(offset[i][2]+110);
  }
}

void fwdPose(){
  for (int i=1; i<6; i+=2)
  {
    mot[i][0].write(90);
    mot[i][1].write(offset[i][1]+34);
    mot[i][2].write(offset[i][2]+40);
  }
}


void Rotate(){
   Serial.write("Rotate"); // évite un obstacle, rotation sur lui même 
   
   mot[0][2].write(45);
   mot[2][2].write(45);
   mot[4][2].write(45); // patte basse 
   mot[0][1].write(150);
   mot[2][1].write(150); // patte  milieu
   mot[4][1].write(150); // 3premières pattes se lèvent FINI
 
   delay(500);
   mot[0][0].write(0);
   mot[2][0].write(0);
   mot[4][0].write(0);//rotation du buste 1  FINI

   delay(500);
   
   mot[0][2].write(135);
   mot[2][2].write(135);
   mot[4][2].write(135);
   mot[0][1].write(30);
   mot[2][1].write(30);
   mot[4][1].write(30);// abaissement des 3 première pattes
   
   delay(500);
   mot[1][2].write(45);
   mot[4][2].write(45);
   mot[5][2].write(45);
   mot[1][1].write(150);
   mot[3][1].write(150);
   mot[5][1].write(150);// on lève les 3 pattes suivantes
   
   delay(500);
   mot[1][0].write(0);
   mot[3][0].write(0);
   mot[4][0].write(0);// 2ème rotation
   
   
   delay(500);
   mot[1][2].write(135);
   mot[3][2].write(135);
   mot[5][2].write(135);
   mot[1][1].write(30);
   mot[3][1].write(30);
   mot[5][1].write(30);
   delay(500); // on baisse les pattes 

   mot[0][0].write(90);
   mot[1][0].write(90);
   mot[2][0].write(90);
   mot[3][0].write(90);
   mot[4][0].write(90);
   mot[5][0].write(90); // rotation final fin de cycle
}


//former doStuff
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
//  for (int i=0; i<6; i+=2)
//  {
//    mot[i][0].write(90);
//    mot[i][1].write(offset[i][1]+100);
//    mot[i][2].write(offset[i][2]+110);
//  }
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




