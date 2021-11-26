# UNO_MPU6050_self_balancing_board
School project of making a gimbal(Self-balancing board) use 2 servos, MPU6050 gyroscope sensor and UNO

Connect the servo to pin 4(as x-axis), pin 8(as y-axis)
connect the MPU6050 as 5V>VCC; GND>GND; A4>SDL; A5>SDA
Since the servo I am using is MG996R, it needs an extra power source
(my case is a 9V battery, and my control board have an buck convertor to meet the current requirement of the servo)

