/*
/* MEB Cover Sensor v2.0
*  All righs GPL-3.0 License
*  https://github.com/andreagavazzi/ag_perception
*/

#include <math.h>
#include <Ultrasonic.h>
#include <SHT1x.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/Temperature.h>
#include <sensor_msgs/RelativeHumidity.h>
#include <sensor_msgs/Range.h>

//Grove-Ultrasonic_Ranger
Ultrasonic ultrasonic(4);  

//Init SHT10 (dataPin, clockPin)
SHT1x sht1x(3, 2);


unsigned long pub_timer;

ros::NodeHandle nh;

//Function to assign fixed data to ultrasonic sensors in ros messages
void sensor_msg_init(sensor_msgs::Range &range_name, char *frame_id_name)
{
  range_name.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_name.header.frame_id = frame_id_name;
  range_name.field_of_view = 0.0872665;
  range_name.min_range = 0.02;
  range_name.max_range = 3.50;
}

//Lights Subscriber
//void lightsCb( const std_msgs::Empty& toggle_msg){
//  digitalWrite(6, HIGH-digitalRead(6));   // toggle the lights
//}
//ros::Subscriber<std_msgs::Empty> sub_led("toggle_lights", &lightsCb );

//Temperature Publisher
sensor_msgs::Temperature temp_msg;
ros::Publisher pub_temp("/temperature", &temp_msg);

//Humidity Publisher
sensor_msgs::RelativeHumidity hum_msg;
ros::Publisher pub_hum("/humidity", &hum_msg);

//Range Sensors Publishers
sensor_msgs::Range range;
ros::Publisher pub_range("/ultrasound", &range);


void setup()
{ 

  // pinMode(6, OUTPUT); //Led

  //Node, publisher e subscribers
  nh.initNode();
  nh.advertise(pub_temp);
  nh.advertise(pub_range);
  nh.advertise(pub_hum);
  //nh.subscribe(sub_led);
  
  //Temperature msg fxed data
  temp_msg.header.frame_id = "/temperature_link";
  temp_msg.variance = 0;  //As unknown to me

  //Humidity msg fxed data
  hum_msg.header.frame_id = "/humidity_link";
  hum_msg.variance = 0;  //As unknown to me

  //Ultrasound fixed data filled by my function
  sensor_msg_init(range, "/ultrasound");

}


void loop()
{

  // Read the temperature as Celsius
  float temperature = sht1x.readTemperatureC();

  // Read the humidity in %
  float humidity = sht1x.readHumidity();
  
  // Read the range
  float RangeInMeters = ultrasonic.MeasureInCentimeters()/100.0;

  unsigned long currentMillis = millis();
  if (currentMillis >= pub_timer+500) //publish every 50 milliseconds
  {
    pub_timer = currentMillis+500;

    temp_msg.header.stamp = nh.now();
    temp_msg.temperature = temperature;
    pub_temp.publish(&temp_msg);

    hum_msg.header.stamp = nh.now();
    hum_msg.relative_humidity = humidity;
    pub_hum.publish(&hum_msg);

    range.header.stamp = nh.now();
    range.range = RangeInMeters;
    pub_range.publish(&range);

    }
   
   nh.spinOnce();
}
