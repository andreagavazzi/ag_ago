/*
/* MEB Cover Sensor v1.0
*  All righs GPL-3.0 License
*  https://github.com/andreagavazzi/ag_perceptiondetects 
*/

#include <math.h>
#include <Ultrasonic.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/Temperature.h>
#include <sensor_msgs/Range.h>

//Grove - Temperature Sensor
const int pinTempSensor = A0;     // Temperature Sensor connect to A0
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

//Grove-Ultrasonic_Ranger
Ultrasonic ultrasonic_r(4);  
Ultrasonic ultrasonic_l(2);

unsigned long pub_timer;

ros::NodeHandle nh;

//Function to assign fixed data to both sensors in ros messages
void sensor_msg_init(sensor_msgs::Range &range_name, char *frame_id_name)
{
  range_name.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_name.header.frame_id = frame_id_name;
  range_name.field_of_view = 0.0872665;
  range_name.min_range = 0.02;
  range_name.max_range = 3.50;
}

//Lights Subscriber
void lightsCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(6, HIGH-digitalRead(6));   // toggle the lights
}
ros::Subscriber<std_msgs::Empty> sub_led("toggle_lights", &lightsCb );


//Temperature Publisher
sensor_msgs::Temperature temp_msg;
ros::Publisher pub_temp("temperature", &temp_msg);

//Range Sensors Publishers
sensor_msgs::Range range_right;
ros::Publisher pub_range_right("/ultrasound_right", &range_right);
sensor_msgs::Range range_left;
ros::Publisher pub_range_left("/ultrasound_left", &range_left);



void setup()
{ 
  pinMode(6, OUTPUT);

  //Node, publisher e subscribers
  nh.initNode();
  nh.advertise(pub_temp);
  nh.advertise(pub_range_right);
  nh.advertise(pub_range_left);
  nh.subscribe(sub_led);
  
  //Temperature msg fxed data
  temp_msg.header.frame_id = "/temperature_link";
  temp_msg.variance = 0;  //As unknown to me

  //Ultrasound fixed data filled by my function
  sensor_msg_init(range_right, "/ultrasound_right");
  sensor_msg_init(range_left, "/ultrasound_left");
}



void loop()
{
  int a = analogRead(pinTempSensor);
  float R = 1023.0/a-1.0;
  R = R0*R;
  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;

  float RangeInMeters_r = ultrasonic_r.MeasureInCentimeters()/100.0;
  float RangeInMeters_l = ultrasonic_l.MeasureInCentimeters()/100.0;

  
  unsigned long currentMillis = millis();
  if (currentMillis >= pub_timer+50) //publish every 50 milliseconds
  {
    pub_timer = currentMillis+50;

    temp_msg.header.stamp = nh.now();
    temp_msg.temperature = temperature;
    pub_temp.publish(&temp_msg);

    range_right.header.stamp = nh.now();
    range_right.range = RangeInMeters_r;
    pub_range_right.publish(&range_right);

    range_left.header.stamp = nh.now();
    range_left.range = RangeInMeters_l;
    pub_range_left.publish(&range_left);
    }
   
   nh.spinOnce();
}
