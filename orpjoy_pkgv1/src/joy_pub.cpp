// This is a node to publish msgs with joystick button presses (this node  is only tested & used with the xbox one controller at the momen)

// Below are the standard headers
#include <chrono>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <iostream>

// Below are the standard headers for ros2
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
// Below is the header to get joystick input from bluetooth communication.
#include <linux/joystick.h>
// Below are the standard namespaces to shorten the code.
using namespace std;
using namespace std::chrono_literals;

 auto message = std_msgs::msg::Int32(); // node msg is created.
 // below is the struct for the joystick values create
 // this node only uses the button values for this node but you can use more if you want to
 //but i recommend to  look for this repo as a example: https://github.com/t-kiyozumi/joystick_on_linux.git
typedef struct
{
  uint16_t X;
  uint16_t Y;
  uint16_t A;
  uint16_t B;
  uint16_t LB;
  uint16_t LT;
  uint16_t RB;
  uint16_t RT;
  uint16_t start;
  uint16_t back;
  int16_t axes1_x;
  int16_t axes1_y;
  int16_t axes0_x;
  int16_t axes0_y;
} controler_state;

void write_controler_state(controler_state *controler, js_event event) // this fuction writes the controller state and publish the node values 
{
   
  switch (event.type)
  {
  case JS_EVENT_BUTTON:

  auto node = rclcpp::Node::make_shared("joy_publisher");
  auto publisher = node->create_publisher<std_msgs::msg::Int32>("joystick_topic", 10);
  // below are the button commands to publish the message data.
   
    if (event.number == 1)
    {
      controler->B = event.value;

     
         message.data = 1;
         publisher->publish(message);
          RCLCPP_INFO(node->get_logger(), "Publishing joystick button b:'%i'", message.data);
    }
    if (event.number == 0)
    {
      controler->A = event.value;

         message.data = 0;
         publisher->publish(message);
         RCLCPP_INFO(node->get_logger(), "Publishing joystick button a: x'%i'", message.data);
    }
    if (event.number == 3)
    {
      controler->X = event.value;

          message.data = 3;
           publisher->publish(message);
         RCLCPP_INFO(node->get_logger(), "Publishing joystick button a: x'%i'", message.data);
    }
    if (event.number == 4)
    {
      controler->Y = event.value;
    
       message.data = 4;
        publisher->publish(message);
         RCLCPP_INFO(node->get_logger(), "Publishing joystick button y:'%i'", message.data);
   
    }
         if (event.number == 6)
    {
      controler->LB = event.value;
    
       message.data = 6;
        publisher->publish(message);
         RCLCPP_INFO(node->get_logger(), "Publishing joystick value:'%i'", message.data);
    }
    if (event.number == 7)
    {
      controler->RB = event.value;
  
       message.data = 7;
        publisher->publish(message);
         RCLCPP_INFO(node->get_logger(), "Publishing joystick button rb:'%i'", message.data);
          rclcpp::shutdown();
         std::cout << "node is shutdown" << '\n';
    }
  
  }
  }

  


int main(int argc, char * argv[])
{    rclcpp::init(argc, argv); // Initialise rclcpp
 
  int fd = open("/dev/input/js0", O_RDONLY); 
  struct js_event event;
  controler_state *controler;
  controler = (controler_state *)malloc(sizeof(controler_state));


  while (1) // now the code publish msgs created by a button presses in a loop.
  {
    read(fd, &event, sizeof(event));
    write_controler_state(controler, event);
  

     usleep(1000);

  
  }


  
 
  return 0;

}