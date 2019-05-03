#include <Servo.h>
Servo esc_signal_12, esc_signal_13, esc_signal_8, esc_signal_7;

void setup()
{
  esc_signal_12.attach(12);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal_12.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  esc_signal_13.attach(13);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal_13.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  esc_signal_8.attach(8);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal_8.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  esc_signal_7.attach(7);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal_7.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  delay(4000);            //ESC initialization delay.
}

void loop()
{
double RPM = 4300.0;
double PWM_8 = (RPM+3422.0)/64.5; 
double PWM_7 = (RPM+4022.0)/74.7;
double PWM_13 = (RPM+3374.0)/66.1;
double PWM_12 = (RPM+3148.0)/65.8;

esc_signal_12.write(PWM_12);    //Vary this between 40-130 to change the speed of motor. Higher value, higher speed.
esc_signal_13.write(PWM_13);    //Vary this between 40-130 to change the speed of motor. Higher value, higher speed.
esc_signal_8.write(PWM_8);    //Vary this between 40-130 to change the speed of motor. Higher value, higher speed.
esc_signal_7.write(PWM_7);    //Vary this between 40-130 to change the speed of motor. Higher value, higher speed.

delay(15);
}
