#include <ArduinoHardware.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

//geometry_msgs::Twist msg;
float dir=0;
float ang=0;
void motorControl(const geometry_msgs::Twist& msg){
  
dir=msg.linear.x;
ang=msg.angular.z;


 
 

  
 
  
}

//ros::Publisher pub("husky/cmd_vel", &msg);

ros::Subscriber<geometry_msgs::Twist> sub("turtle1/cmd_vel",motorControl);

void setup()
{
 nh.initNode();
 //nh.advertise(pub);
 pinMode(5,OUTPUT);
 pinMode(3,OUTPUT);
 nh.subscribe(sub);
}

void loop()
{
  //analogWrite(5,125);
  //analogWrite(3,125);
 nh.spinOnce();
 
 if(dir==2.0){
  analogWrite(3,210);
  analogWrite(5,210);
  delay(500);
  
  
 }
 else if(dir==-2.0){

  analogWrite(5,20);
  analogWrite(3,20);
  delay(500);
 }



else if(ang==2.0){

  analogWrite(5,20);
  analogWrite(3,210);
  delay(500);
 }

 else if (ang==-2.0){

  analogWrite(5,210);
  analogWrite(3,20);
  delay(500);
 }
dir=0;
ang=0;
 analogWrite(5,125);
 analogWrite(3,125);

 }

