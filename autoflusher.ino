#include <ServoTimer1.h>
ServoTimer1 servo1;

int sensor=0;
int sensorPin=5; //distance sensor on analog pin 5

int PreparingToFlush=0;
int sample1;
int sample2;
int sample3;
int sample4;

void setup() {
  Serial.begin(9600);         
  servo1.attach(10); //servo data line on pin 10
  servo1.write(3);
 
// digitalWrite(3,HIGH); //(an LED)
}


void loop() {
sensor=analogRead(sensorPin);

Serial.println(sensor);


if (PreparingToFlush==0){ 
if (sensor > 90){ //if distance sensor detects someone
  delay(1000);  // wait
  sample1=analogRead(sensorPin); //take a sample of the data
  Serial.println("Sensing");
  delay(300);
  sample2=analogRead(sensorPin);
  delay(300);
  sample3=analogRead(sensorPin);
  delay(400);
  sample4=analogRead(sensorPin);
 
  sensor= (sample1 + sample2 + sample3 + sample4)/4;
  if (sensor > 90){ // check again to make sure someone is actually there
  PreparingToFlush=1;
  digitalWrite(13, HIGH);
 
  Serial.println(sensor);
  }
}
}

if (PreparingToFlush==1){ //if a person has been detected
  if (sensor < 60){ // if the person has now left
  delay(1000);
  sensor=analogRead(sensorPin);
  if (sensor < 60){
  Serial.println("Flushing");
  servo1.write(175); //FLUSH
  digitalWrite(13, LOW);
  delay(9000);
  servo1.write(3);
  delay(1000);
 
  PreparingToFlush=0;  //reset the trigger
}
} 
} 
 
 
  delay(10);
}
