#include <Wire.h>
#include <MPU6050.h>
 
#define first_motor_pin1 5
#define first_motor_pin2 6
#define second_motor_pin1 9
#define second_motor_pin2 10

MPU6050 sensor;
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
int first_motor_speed;
int second_motor_speed;

void setup ( )
{
  Wire.begin( );
  Serial.begin (9600);
  Serial.println ("Initializing the sensor");
  sensor.initialize ( );
  Serial.println(sensor.testConnection( ) ? "Successfully Connected" : "Connection failed");
  delay(1000);
  Serial.println("Taking Values from the sensor");
  delay(1000);
}

void loop ( )
{
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, -125, 125);
  first_motor_speed = 125+ax;
  second_motor_speed = 125-ax;
  
  Serial.print ("Motor1 Speed = ");
  Serial.print (first_motor_speed, DEC);
  Serial.print (" && ");
  Serial.print ("Motor2 Speed = ");
  Serial.println (second_motor_speed, DEC);
   
  analogWrite (first_motor_pin2, first_motor_speed);
  analogWrite (second_motor_pin2, second_motor_speed);
  delay (200);
}
