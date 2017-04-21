#include <Bounce.h>
//#include "xinput.h"

Bounce A_button = Bounce(0, 10);
Bounce B_button = Bounce(1, 10);  
Bounce X_button = Bounce(2, 10);  
Bounce Y_button = Bounce(3, 10); 
Bounce start_button = Bounce(8, 10);
//Bounce select_button = Bounce(7, 10);
//Bounce home_button = Bounce(8, 10);
Bounce dpad_left = Bounce (4, 10);
Bounce dpad_right = Bounce (5, 10);
Bounce dpad_up = Bounce (6, 10);
Bounce dpad_down = Bounce (7, 10);

//10 ms debounce time

  uint8_t hatu = 0;// this bit of code drives the dpad to be the hat switch. I stole it from somewhere(public domain of course) and I don't know how it works. It just does.
  uint8_t hatr = 0;
  uint8_t hatd = 0;
  uint8_t hatl = 0;
   int GetHatState() {
    uint8_t x, y;
    const static int16_t dpad_lookup[4][4] = {
      { -1, 270,  90, -1},
      {  0, 315,  45, -1},
      {180, 225, 135, -1},
      { -1,  -1,  -1, -1}
    };
    
    y = hatu | (hatd << 1);
    x = hatl | (hatr << 1);
    
    return dpad_lookup[y][x];
  }
  
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
int inputmax = 1023;
int inputmin = 0;
int inputrange;
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
  digitalWrite(13, HIGH); //this is the led BTW.
  Joystick.hat(-1);// makes the hat switch behave itself. Damn you hat switch! why can't you default to -1 instead of 0!?
  Xrange = Xmax - Xmin;
  Yrange = Ymax - Ymin;
  Zrange = Zmax - Zmin;
  ZRrange = ZRmax - ZRmin;
  Rtriggerrange = Rtriggermax - Rtriggermin;
  Ltriggerrange = Ltriggermax - Ltriggermin;
  inputrange = inputmax - inputmin;
  Joystick.useManualSend(true);

}

void loop() {
  A_button.update();
  B_button.update();
  X_button.update();
  Y_button.update();
  start_button.update();
  dpad_left.update();
  dpad_right.update();
  dpad_up.update();
  dpad_down.update();
  /*select_button.update();
  home_button.update();
   */
  
  //Joystick.Zrotate(512);
  //Joystick.Xrotate(512);(note to self: Learn how to get Xrotate and Yrotate working.
  //Joystick.Z(512);

  /* this is a range conversion formula which translates the 
   *  analog signal range into a viable range for joysticks.
   */
// for reference (New Value = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
    
    //Y axis of left stick(the analog signal from the Y axis pin is inverted)
  
  if (analogRead(axisY) < Ymax)
  {
  if (analogRead(axisY) > Ymin)
  {
  axisYvalue = ((((analogRead(axisY) - Ymin) * inputrange) / Yrange) + inputmin );  
  Joystick.Y (inputmax - axisYvalue);//<-this extra math uninverts the Y axis range
  }}
  // the overflow and underflow protection code for the Y axis needs to be reversed because of the inversion
  if (analogRead(axisY) >= Ymax)
  {
    Joystick.Y (inputmin);
  }

  if (analogRead(axisY) <= Ymin)
  {
    Joystick.Y (inputmax);
  }
  
    //X axis of left stick
  
  if (analogRead(axisX) < Xmax)
  {
  if (analogRead(axisX) > Xmin)
  {
  axisXvalue = ((((analogRead(axisX) - Xmin) * inputrange) / Xrange) + inputmin );  
  Joystick.X (axisXvalue);
  }}
  
  if (analogRead(axisX) >= Xmax)
  {
    Joystick.X (inputmax);
  }

  if (analogRead(axisX) <= Xmin)
  {
    Joystick.X (inputmin);
  }

    //Z axis of right stick(up-down)

  if (analogRead(axisZ) < Zmax)
  {
  if (analogRead(axisZ) > Zmin)
  {
  axisZvalue = ((((analogRead(axisZ) - Zmin) * inputrange) / Zrange) + inputmin ); 
  Joystick.Z (inputmax - axisZvalue);
  }}

    if (analogRead(axisZ) >= Zmax)
  {
    Joystick.Z (inputmin);
  }

  if (analogRead(axisZ) <= Zmin)
  {
    Joystick.Z (inputmax);
  }
  
    //Zrotate axis of left stick(left-right)
  
  if (analogRead(axisZR) < ZRmax)
  {
  if (analogRead(axisZR) > ZRmin)
  {
  axisZRvalue = ((((analogRead(axisZR) - ZRmin) * inputrange) / ZRrange) + inputmin );  
  Joystick.Zrotate (axisZRvalue);
  }}

    if (analogRead(axisZR) >= ZRmax)
  {
    Joystick.Zrotate (inputmax);
  }

  if (analogRead(axisZR) <= ZRmin)
  {
    Joystick.Zrotate (inputmin);
  }

    //Left Slider axis for left trigger

  if (analogRead(Lslider) < Ltriggermax)
  {
  if (analogRead(Lslider) > Ltriggermin)
  {
  Lslidervalue = ((((analogRead(Lslider) - Ltriggermin) * inputrange) / Ltriggerrange) + inputmin );  
  Joystick.sliderLeft(Lslidervalue);
  }}
  
  if (analogRead(Lslider) >= Ltriggermax)
  {
    Joystick.sliderLeft (inputmax);
  }

  if (analogRead(Lslider) <= Ltriggermin)
  {
    Joystick.sliderLeft (inputmin);
  }

    //Right Slider axis for Right trigger

  if (analogRead(Rslider) < Rtriggermax)
  {
  if (analogRead(Rslider) > Rtriggermin)
  {
  Rslidervalue = ((((analogRead(Rslider) - Rtriggermin) * inputrange) / Rtriggerrange) + inputmin );  
  Joystick.sliderRight(Rslidervalue);
  }}
  
  if (analogRead(Rslider) >= Rtriggermax)
  {
    Joystick.sliderRight (inputmax);
  }

  if (analogRead(Rslider) <= Rtriggermin)
  {
    Joystick.sliderRight (inputmin);
  }
  
  
  
 
  //checking to see if buttons are pressed

  //Buttons A B X Y START
  
  if (A_button.fallingEdge()) {
    Joystick.button(1, 1); 
  }
  if (B_button.fallingEdge()) {
    Joystick.button(2, 1);  
  }
  if (X_button.fallingEdge()) {
    Joystick.button(3, 1);
  }
  if (Y_button.fallingEdge()) {
    Joystick.button(4, 1);
  }
  if (start_button.fallingEdge()) {
    Joystick.button(5, 1);
  }

  //D-pad buttons
  
  if (dpad_left.fallingEdge()) {
    hatl = 1;
    Joystick.hat(GetHatState());
  }
  if (dpad_right.fallingEdge()) {
    hatr = 1;
    Joystick.hat(GetHatState());
  }
  if (dpad_up.fallingEdge()) {
    hatu = 1;
    Joystick.hat(GetHatState());
  }
  if (dpad_down.fallingEdge()) {
    hatd = 1;
    Joystick.hat(GetHatState());
  }
  /*if (select_button.fallingEdge()) {//My controller design doesn't have select and home buttons at the moment(or RB and LB for that matter)
    Joystick.button(8, 1);
  }
  if (home_button.fallingEdge()) {
    Joystick.button(9, 1);
  }
  */
  

 //Checking to see if buttons are released
 //Buttons A B X Y Start
  if (A_button.risingEdge()) {
    Joystick.button(1,0);  
  }
  if (B_button.risingEdge()) {
    Joystick.button(2, 0);
  }
  if (X_button.risingEdge()) {
    Joystick.button(3, 0);
  }
  if (Y_button.risingEdge()) {
    Joystick.button(4, 0);
  }
  if (start_button.risingEdge()) {
    Joystick.button(5, 0);
  }

  //D-pad buttons
  
  if (dpad_left.risingEdge()) {
    hatl = 0;
    Joystick.hat(GetHatState());
  }
  if (dpad_right.risingEdge()) {
    hatr = 0;
    Joystick.hat(GetHatState());
  }
  if (dpad_up.risingEdge()) {
    hatu = 0;
    Joystick.hat(GetHatState());
  }
  if (dpad_down.risingEdge()) {
    hatd = 0;
    Joystick.hat(GetHatState());
  }
 /* if (select_button.risingEdge()) {//I really need to find a decent place to put some tact switches for these.
    Joystick.button(8, 0);
  }
  if (home_button.risingEdge()) {
    Joystick.button(9, 0);
  }
  */
  Joystick.send_now();
}

