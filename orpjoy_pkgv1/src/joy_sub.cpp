
// This is  just a simple ros2 jazzy  member subscriber node to receive publisher msg to control motor direction.
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <wiringPi.h>
using namespace std;
using std::placeholders::_1;

// below are the pins to control the motor direction.
int ia2 = 14;
int ib2 = 15;
int ia1 = 18;
int ib1 = 23;



// this are the main functions to to control the motor directions with the direction printed.

void right(){

    digitalWrite(ia1,LOW);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,HIGH);
    cout << "Robot moves rightwards"<< '\n';
}


void left(){

    digitalWrite(ia1,HIGH);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,LOW);
    cout << "Robot moves leftwards"<< '\n';
}

void backward(){

    digitalWrite(ia1,HIGH);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,HIGH);
    cout << "Robot moves backwards"<< '\n';
}

void forward(){

    digitalWrite(ia1,LOW);
    digitalWrite(ia2,HIGH);
    digitalWrite(ib1,HIGH);
    digitalWrite(ib2,LOW);
    cout << "Robot moves forward"<< '\n';
}


void stop(){

    digitalWrite(ia1,LOW);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,LOW);
    cout << "Robot stops"<< '\n';
}


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("joy_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int32>(
      "joystick_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));


    
    wiringPiSetupGpio();

    pinMode(ia1,OUTPUT);
    pinMode(ia2,OUTPUT);
    pinMode(ib1,OUTPUT);
    pinMode(ib2,OUTPUT);
  }

private:
  void topic_callback(const std_msgs::msg::Int32 & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I receive  joystick value: '%i'", msg.data);

// below are the joystick button commands to control the motor direction.
  if (msg.data == 4) { // y button
forward();
  
  }

  if (msg.data == 0) { // a button
backward();
  
  }
  if (msg.data == 3) { // x button
left();

   }

  if (msg.data == 1) { // b button
right(); 

  }
  if (msg.data == 6) {  // lb button
stop();
  }

    if (msg.data == 7) {  // rb button
 rclcpp::shutdown();
  
  }

    
  }
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;

};
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}