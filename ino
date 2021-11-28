#include "Wire.h"
#include <MPU6050_light.h>
#include <Servo.h>

Servo servo4; // control the x-axis
Servo servo8; // control the y-axis

int period = 50;

unsigned long time;

float error_x;
float error_x_previous;
float x_setpoint = 98;

float error_y;
float error_y_previous;
float y_setpoint = 92.5;

float kp_x=1; 
float ki_x=0.0001; 
float kd_x=0.1; 

float kp_y=1 ; 
float ki_y=0.0001; 
float kd_y=0.1; 

double PID_p_x, PID_i_x, PID_d_x, PID_total_x;
double PID_p_y, PID_i_y, PID_d_y, PID_total_y;

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();

  servo4.attach(4);
  servo8.attach(8);
  servo4.write(x_setpoint);
  servo8.write(y_setpoint);
  delay(500);
  Serial.println("Motor Finish Setup");
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  
  mpu.calcOffsets();
  mpu.getFilterGyroCoef();
  mpu.update(); 
  
  Serial.println(-mpu.getAngleY());
  Serial.println(mpu.getAngleX());
  Serial.println("Done!\n");
}


void loop() {

    if(time<5000){
    time = millis();
    mpu.update();
    Serial.println("Please Wait for a while");
    Serial.println(time);
    }
    
    else{
    if (millis() > time+period){
    time = millis();
    mpu.update();
    
    error_y = y_setpoint - mpu.getAngleY();
    error_x = x_setpoint - mpu.getAngleX();
    
    PID_p_y = kp_y * error_y;
    float diff_y = error_y - error_y_previous;     
    PID_d_y = kd_y*((error_y - error_y_previous)/period);    
    if(89.5 < error_y && error_y < 93.5)
    {
      PID_i_y = PID_i_y + (ki_y * error_y);
    }
    else
    {
      PID_i_y = 0;
    }
    
    PID_total_y = PID_p_y + PID_i_y + PID_d_y; 

     
    PID_p_x = kp_x * error_x;
    float diff_x = error_x - error_x_previous;     
    PID_d_x = kd_x*((error_x - error_x_previous)/period);
    if(95 < error_x && error_x < 101)
    {
      PID_i_x = PID_i_x + (ki_x * error_x);
    }
    else
    {
      PID_i_x = 0;
    }
    
    PID_total_x = PID_p_x + PID_i_x + PID_d_x;

    servo8.write(PID_total_y);
    servo4.write(PID_total_x);
  
    Serial.println(-mpu.getAngleY());
    Serial.println(mpu.getAngleX());

    error_y_previous = error_y;  
    error_x_previous = error_x; 
      }
    }
}
