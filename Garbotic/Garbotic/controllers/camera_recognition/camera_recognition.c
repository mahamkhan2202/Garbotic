#include <stdio.h>
#include <webots/camera.h>
#include <webots/camera_recognition_object.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define SPEED 5
#define TIME_STEP 64

void straight()
{
  WbDeviceTag left_motor, right_motor;
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor,  SPEED);
  wb_motor_set_velocity(right_motor, SPEED);
}

void stop(int ret)
{
  WbDeviceTag left_motor, right_motor;
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  if (ret ==1)
  {
  wb_motor_set_velocity(left_motor,  -SPEED);
  wb_motor_set_velocity(right_motor, 0.0);
  }
  else
  {
  wb_motor_set_velocity(left_motor,  0.0);
  wb_motor_set_velocity(right_motor, 0.0);
  }

}

void left_turn()
{
  WbDeviceTag left_motor, right_motor;
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor,  -SPEED);
  wb_motor_set_velocity(right_motor, SPEED);
}

int object (int id)
{
  int k = 0;
  if (id == 150)
  {
   k=1;
  }
  else if (id == 159)
  {
   k=2;
  }
  return k;
}

int main() {
  WbDeviceTag camera, left_motor, right_motor;
  int i=0;
  wb_robot_init();
  camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, TIME_STEP);
  wb_camera_recognition_enable(camera, TIME_STEP);
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  
  
  while (wb_robot_step(TIME_STEP) != -1) {
    const WbCameraRecognitionObject *objects = wb_camera_recognition_get_objects(camera);
    int trash = object(objects[i].id);
    if (trash ==0)
    {
      left_turn();
    }
    if  (trash == 1)
    {
     if (objects[i].position_on_image[0] < 125)
     {
      left_turn();
     }
     else if (objects[i].position[0] > 0.2)
     {
      straight ();
     }
     else
     {
      stop(1);
     }
     }
    if  (trash == 2 && objects[i].id != 150)
    {
     if (objects[i].position_on_image[0] < 125)
     {
      left_turn();
     }
     else if (objects[i].position[0] > 0.2)
     {
      straight ();
     }
     else
     {
      stop(2);
     }
     }
    }
     
  wb_robot_cleanup();
  return 0;
}
