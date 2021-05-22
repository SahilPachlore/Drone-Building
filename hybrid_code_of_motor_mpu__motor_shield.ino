#include <AFMotor.h>
#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2); 


MPU6050 sensor;
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
int valMotor1;  // first_motor_speed
int valMotor2; //second_motor_speed

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
}

void loop ( )
{
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, -125, 125);
  valMotor1= 125+ax;  //first_motor_speed
  
  valMotor2 = 125-ax; //second_motor_speed
  
  Serial.print ("Motor1 Speed = ");
  Serial.print (valMotor1, DEC);
  Serial.print (" && ");
  Serial.print ("Motor2 Speed = ");
  Serial.println (valMotor2, DEC);
   
  if(valMotor1 >0 && valMotor1 <255){
    motor2.setSpeed(valMotor2);
    
  }
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(200);
  }
