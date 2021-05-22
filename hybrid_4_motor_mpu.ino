#include <AFMotor.h>
#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4); 


MPU6050 sensor;
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
int valMotor1;  // first_motor_speed
int valMotor2; //second_motor_speed
int valMotor3;
int valMotor4;
void setup ( )
{
  Wire.begin( );
  Serial.begin (9600);
  Serial.println ("Initializing the MPU");
  sensor.initialize ( );
  Serial.println(sensor.testConnection( ) ? "Successfully Connected" : "Connection failed");
  delay(1000);
  Serial.println("Taking Values from the sensor");
  delay(1000);
  motor1.setSpeed(100); // we know speed between 20 to 250
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(100);
}

void loop ( )
{
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, -125, 125);
  ay = map(ay,-17000,17000,-125,125);
  valMotor1= 125+ax;  //first_motor_speed
  valMotor2 = 125-ax; //second_motor_speed
  valMotor3 = 125-ay; //third_motor_speed
  valMotor4 = 125-ay; //four_motor_speed
  
  
  Serial.print ("Motor1 Speed = ");
  Serial.print (valMotor1, DEC);
  Serial.print (" && ");
  Serial.print ("Motor2 Speed = ");
  Serial.println (valMotor2, DEC);
  Serial.print (" && ");
  Serial.print ("Motor3 Speed = ");
  Serial.println (valMotor3, DEC);
  Serial.print (" && ");
  Serial.print ("Motor4 Speed = ");
  Serial.println (valMotor4, DEC);
   
  if(valMotor1 >0 && valMotor1 <255){
    motor2.setSpeed(valMotor2);
    
  }
   if(valMotor3 >0 && valMotor3 <255){
    motor4.setSpeed(valMotor3);
    
  }
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(200);
  }
