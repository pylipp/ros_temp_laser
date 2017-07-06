//www.elegoo.com
//2016.06.13

#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int16.h>

/*
 * components:
 * - laser module at D9
 * - temperature module at A0
 */

int  ledPin  =  9;   // select the pin for  the LED

ros::NodeHandle nh;
bool laserOn = false;

void switch_laser_cb(const std_msgs::Empty& msg) {
  digitalWrite(ledPin, (laserOn) ? LOW : HIGH);
  laserOn = !laserOn;
  delay(50);
}
ros::Subscriber<std_msgs::Empty> sub_switch_laser("switch_laser", switch_laser_cb);

std_msgs::Int16 msg_temperature;
ros::Publisher pub_temperature("temperature", &msg_temperature);

int  sensorPin  =  A0;     // select the input  pin for  the potentiometer 
int  sensorValue =  0;  // variable to  store  the value  coming  from  the sensor
int counter = 0;

void publishTemperature() 
{
  if (counter % 50 == 0) {
  sensorValue = analogRead(sensorPin);
  msg_temperature.data = sensorValue;
  pub_temperature.publish(&msg_temperature);
  }
  counter++;
}

void setup()
{
  nh.initNode();
  nh.subscribe(sub_switch_laser);
  nh.advertise(pub_temperature);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop(){
  nh.spinOnce();
  publishTemperature();
  delay(10);
}
/* 
sensorValue =  analogRead(sensorPin);
if (sensorValue > threshold) {
digitalWrite(ledPin,  HIGH); 
delay(50); 
digitalWrite(ledPin,  LOW);
delay(50);
}
Serial.println(sensorValue,  DEC);
}*/

