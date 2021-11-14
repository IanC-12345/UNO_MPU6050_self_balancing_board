#include "Wire.h"
#include <MPU6050_light.h>
#include <Servo.h>

Servo servo4;
Servo servo8;

MPU6050 mpu(Wire);
unsigned long timer = 0;

int period = 50;

double error_x;
double error_x_previous;
double x_setpoint = 98;

float error_y;
float error_y_previous;
float y_setpoint = 92.5;

float kp=1; 
float ki=0; 
float kd=0; 
double PID_p, PID_i, PID_d, PID_total;

float time;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  servo4.attach(4); // x-axis servo
  servo8.attach(8); // y-axis servo
  servo4.write(98); // centre the platform
  servo8.write(92.5); centre the platform
  delay(500);
  Serial.println("Motor Finish Setup");
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  if((millis()-timer)>100){ // print data every 100ms
	Serial.print("X : ");
	Serial.print(mpu.getAngleX());
	Serial.print("\tY : ");
	Serial.println(-mpu.getAngleY());
	timer = millis(); 
  }

 if (millis() > time+period)
  {
    time = millis();

  error_x = x_setpoint - mpu.getAngleX();
  error_y = y_setpoint - mpu.getAngleY();

    PID_p = kp * error_y;
    float diff_y = error_y - error_y_previous;     
    PID_d = kd*((error_y - error_y_previous)/period);
    PID_i = PID_i + (ki * error_y);  
    PID_total = PID_p + PID_i + PID_d;  
    
    //PID_total = map(PID_total, -150, 150, 0, 150);
    //if(PID_total < 20){PID_total = 20;}
    //if(PID_total > 160) {PID_total = 160; } 


  Serial.print(error_y);
  servo8.write(error_y);
  Serial.println(servo8.read());


  //servo4.write(error_x);
  //Serial.println(servo4.read());
  error_y_previous - error_y;  
  }

}
