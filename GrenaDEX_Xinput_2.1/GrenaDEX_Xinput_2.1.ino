#include <Bounce.h>
#include "xinput.h"



int axisY = A1; // this is the raw analog value that the Teensy recieves(incidently the Y axis signal is inverted due to the hardware of this project)
int axisYvalue ;// this is the value that is sent to the OS
int axisX = A0; //ditto for the rest of these.
int axisXvalue ;
int axisZ = A2;
int axisZvalue ;
int axisZR = A3;
int axisZRvalue ;
int Lslider = A4;
int Lslidervalue;
int Rslider = A5;
int Rslidervalue;
// these are the minimum and maximum analog values the pins recieve and are used
// to calibrate the sticks and triggers.
int Xmax = 785;
int Xmin = 305;
int Ymax = 705;
int Ymin = 230;
int Zmax = 730;
int Zmin = 290;
//int XRmax;//Teensy doesn't natively support X and Y rotation axis for some
//int XRmin;//reason so I've put these here in case it does in the future(Damnit)
//int YRmax;
//int YRmin;
int ZRmax = 710;
int ZRmin = 280;
int Ltriggermax = 600;
int Ltriggermin = 225;
int Rtriggermax = 605;
int Rtriggermin = 245;
int Xrange;
int Yrange;
int Zrange;
int ZRrange;
int Rtriggerrange;
int Ltriggerrange;
// these variables represent the analog range that the input standard calls for
// example a: Directinput goes from 0 to 1023 on all axis
// example b: Xinput goes from -32768 to 32767 on both axis of both control
// sticks while the triggers go from 0 to 255.
int inputmax = 32767;
int inputmin = -32768;
int inputrange;
int triggermax = 255;
int triggermin = 0;
int triggerrange = 255;
XINPUT controller(NO_LED, 13);// needs this line of code for some reason.
void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP); 
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Xrange = Xmax - Xmin;
  Yrange = Ymax - Ymin;
  Zrange = Zmax - Zmin;
  ZRrange = ZRmax - ZRmin;
  Rtriggerrange = Rtriggermax - Rtriggermin;
  Ltriggerrange = Ltriggermax - Ltriggermin;
  inputrange = inputmax - inputmin;
 


}

void loop() {
  digitalWrite(13, HIGH);
  //read pins
  int A_buttonstate = digitalRead(0);
  int B_buttonstate = digitalRead(1);;
  int X_buttonstate = digitalRead(2);
  int Y_buttonstate = digitalRead(3);
  int START_buttonstate = digitalRead(8);
  int dpad_left = digitalRead (4);
  int dpad_right = digitalRead (5);
  int dpad_up = digitalRead (6);
  int dpad_down = digitalRead (7);
  //int SELECT_buttonstate = digitalRead(7);
  //int HOME_buttonstate = digitalRead(8);
  controller.buttonUpdate(BUTTON_A, !A_buttonstate);
  controller.buttonUpdate(BUTTON_B, !B_buttonstate);
  //controller.buttonUpdate(BUTTON_RB, !C_buttonstate);
  controller.buttonUpdate(BUTTON_X, !X_buttonstate);
  controller.buttonUpdate(BUTTON_Y, !Y_buttonstate);
  //controller.buttonUpdate(BUTTON_LB, !Z_buttonstate);
  controller.buttonUpdate(BUTTON_START, !START_buttonstate);
  //controller.buttonUpdate(BUTTON_BACK, !SELECT_buttonstate);
  //controller.buttonUpdate(BUTTON_L3, !HOME_buttonstate);
  controller.dpadUpdate(!dpad_up, !dpad_down, !dpad_left, !dpad_right);
  //read the stick
  /*This uses a range conversion formula to convert the analog range to the 
  proper range that xinput needs.*/
  
  if (analogRead(axisY) < Ymax)
  {
  if (analogRead(axisY) > Ymin)
  {
  axisYvalue = ((((analogRead(axisY) - Ymin) * inputrange) / Yrange) + inputmin);  
  
  }}
  // the overflow and underflow protection code for the Y axis needs to be reversed because of the inversion
  if (analogRead(axisY) <= Ymin)
  {
    axisYvalue = inputmin;
  }

  if (analogRead(axisY) >= Ymax)
  {
    axisYvalue = inputmax;
  }
  
    //X axis of left stick
  
  if (analogRead(axisX) < Xmax)
  {
  if (analogRead(axisX) > Xmin)
  {
  axisXvalue = ((((analogRead(axisX) - Xmin) * inputrange) / Xrange) + inputmin );  
  
  }}
  
  if (analogRead(axisX) >= Xmax)
  {
    axisXvalue = inputmax;
  }

  if (analogRead(axisX) <= Xmin)
  {
    axisXvalue = inputmin;
  }

    //Z axis of right stick(up-down)

  if (analogRead(axisZ) < Zmax)
  {
  if (analogRead(axisZ) > Zmin)
  {
  axisZvalue = ((((analogRead(axisZ) - Zmin) * inputrange) / Zrange) + inputmin );  
  
  }}

    if (analogRead(axisZ) >= Zmax)
  {
    axisZvalue = inputmax;
  }

  if (analogRead(axisZ) <= Zmin)
  {
    axisZvalue = inputmin;
  }
  
    //Zrotate axis of left stick(left-right)
  
  if (analogRead(axisZR) < ZRmax)
  {
  if (analogRead(axisZR) > ZRmin)
  {
  axisZRvalue = ((((analogRead(axisZR) - ZRmin) * inputrange) / ZRrange) + inputmin );  
  
  }}

    if (analogRead(axisZR) >= ZRmax)
  {
    axisZRvalue = inputmax;
  }

  if (analogRead(axisZR) <= ZRmin)
  {
    axisZRvalue = inputmin;
  }

    //Left Slider axis for left trigger

  if (analogRead(Lslider) < Ltriggermax)
  {
  if (analogRead(Lslider) > Ltriggermin)
  {
  Lslidervalue = ((((analogRead(Lslider) - Ltriggermin) * triggermax) / Ltriggerrange) + triggermin );  
  
  }}
  
  if (analogRead(Lslider) >= Ltriggermax)
  {
    Lslidervalue = triggermax;
  }

  if (analogRead(Lslider) <= Ltriggermin)
  {
    Lslidervalue = triggermin;
  }

    //Right Slider axis for Right trigger

  if (analogRead(Rslider) < Rtriggermax)
  {
  if (analogRead(Rslider) > Rtriggermin)
  {
  Rslidervalue = ((((analogRead(Rslider) - Rtriggermin) * triggermax) / Rtriggerrange) + triggermin );  
  
  }}
  
  if (analogRead(Rslider) >= Rtriggermax)
  {
    Rslidervalue = triggermax;
  }

  if (analogRead(Rslider) <= Rtriggermin)
  {
    Rslidervalue = triggermin;
  }
  
  
  controller.stickUpdate(STICK_LEFT, axisXvalue, axisYvalue);
  controller.stickUpdate(STICK_RIGHT, axisZRvalue, axisZvalue);
  controller.triggerUpdate(Lslidervalue, Rslidervalue);
  //Check for button Presses
  
  if(!A_buttonstate)
  {
    controller.buttonUpdate(BUTTON_A, 1);
  }
  if(!B_buttonstate)
  {
    controller.buttonUpdate(BUTTON_B, 1);
  }
  if(!X_buttonstate)
  {
    controller.buttonUpdate(BUTTON_X, 1);
  }
  if(!Y_buttonstate)
  {
    controller.buttonUpdate(BUTTON_Y, 1);
  }
  if(!START_buttonstate)
  {
    controller.buttonUpdate(BUTTON_START, 1);
  }
  /*if(!SELECT_buttonstate)
  {
    controller.buttonUpdate(BUTTON_BACK, 1);
  }
  if(!HOME_buttonstate)
  {
    controller.buttonUpdate(BUTTON_L3, 1); 
  }*/
  
  
  if 
    (digitalRead(0) == LOW)
    {if
    (digitalRead(1) == LOW)
    {if
    (digitalRead(2) == LOW)
    {if
    (digitalRead(3) == LOW)
    {
    controller.bootloaderJump();
  }}}}
  controller.sendXinput();
  controller.receiveXinput();
  controller.LEDUpdate();
}  



