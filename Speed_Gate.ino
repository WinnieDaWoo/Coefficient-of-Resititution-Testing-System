/*
Coefficient of Restitution Test System
Written by Adam Woo

Board: DFRobot Romeo

This program was designed to use a laserdiode array to identify when an object has entered and left a single plane,
giving the velocity of the object perpendicular to the plane. The program will then analyse the restitution
properties of the object ball by comparing the initial and rebound velocity. All data will be displayed on a 2x16
character LCD.
*/

//-------------------------------------------------------------------------------------
// include libraries
//-------------------------------------------------------------------------------------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x20,16,2);

//-------------------------------------------------------------------------------------
// define constants and variables
//-------------------------------------------------------------------------------------
#define milliPerMicro_to_milePreHour 2237.4145431945
int NUM_BUTTON = 3;
int adc_key_val[5] ={30, 150, 360, 535, 760};
int button, buttonPin = 7;   // choose the input pin (for pushbutton)
int stage, tests, mph, psi;          // variable for setting stages, counting tests, MPH, and PSI
int photocellPin1 = 0, photocellPin2 = 1;     // the cell and 10K pulldown are connected to a0
int buttonPress;
unsigned long SensorOne_timerIn, SensorOne_timerOut, SensorTwo_timerIn, SensorTwo_timerOut;
double timePlaneOne, speedIn, timePlaneTwo, speedOut, COR;    // output variables

void set(int action){
  if(action==1){
    mph = mph + 10;
    if (mph > 70){      // resets desired mph after 70mph because faster speeds require dangerous PSI
      mph = 0;
      lcd.clear();
    }
  }
  else if(action==2){
    stage = 1;          // moves to measure stage
  }

  psi = round((1.2*mph)+13);  // PSI calculations found by data generated empirical curve

  lcd.setCursor(0,0);
  lcd.print("Desired MPH: ");
  lcd.print(mph);
  lcd.setCursor(0,1);
  lcd.print("Desired PSI: ");
  lcd.print(psi);
}

void measure(){
  //-------------------------------------------------------------------------------------
  // loops if nothing has passed though the speed gate
  //-------------------------------------------------------------------------------------
  if (tests == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ready for test");
    tests = 1;
  }

  while (analogRead(photocellPin)<60){}  // while grid unbroken do nothing

  if (tests == 1){
    //-------------------------------------------------------------------------------------
    // first measurement
    //-------------------------------------------------------------------------------------
    SensorOne_timerIn = micros();   //record the time the ball reaches the gate first time
    while (analogRead(photocellPin)>60){} // while grid is broken do nothing
    SensorOne_timerOut = micros();


    tests = 2;      // initiate outbound measurement
  }

  else if (tests == 2){
    //-------------------------------------------------------------------------------------
    // second measurement
    //-------------------------------------------------------------------------------------
    SensorTwo_timerIn = micros(); //record the time the ball reaches the first gate
    while (analogRead(photocellPin)>60){}
    SensorTwo_timerOut = micros();

    tests = 3;
    stage = 2;
  }
}

int get_button(unsigned int input){
  //-------------------------------------------------------------------------------------
  // checks which button has been pressed (not needed if using external buttons)
  //-------------------------------------------------------------------------------------
  int k;
  for (k = 0; k < NUM_BUTTON; k++){
    if (input < adc_key_val[k]){
      return k;
    }
  }
  if (k >= NUM_BUTTON){
    k = 0;     // No valid key pressed
  }
  return k;
}

void setup(){
  //-------------------------------------------------------------------------------------
  // initilize LCD and photoresistor pin
  //-------------------------------------------------------------------------------------
  lcd.init ();
  lcd.backlight ();
  lcd.begin(16,2);
  pinMode(photocellPin, INPUT);      // declare speed gate as analog input
  Serial.begin(9600);
}

void loop(){
  while (stage == 0){
    //-------------------------------------------------------------------------------------
    // push buttons select the desired mph to display the needed PSI, then activates the
    // speedgate for measurement. Allows for measurement system to ignore loading.
    //-------------------------------------------------------------------------------------
    set(button);
    if (button !=0){
      delay(400);
    }
    buttonPress = analogRead(buttonPin);    // read the value from the sensor
    button = get_button(buttonPress);    // convert into key press
  }
  while (stage == 1){
    //-------------------------------------------------------------------------------------
    // all measurement take place in the "measure" function
    //-------------------------------------------------------------------------------------
    measure();
  }

  while (stage == 2){
    //-------------------------------------------------------------------------------------
    // all calculations and printing done after all measurements
    //-------------------------------------------------------------------------------------

    timePlaneOne = (SensorOne_timerOut-SensorOne_timerIn);
    speedIn = (baseball_diameter/timePlaneOne)*milliPerMicro_to_milePreHour;
    timePlaneTwo = (SensorTwo_timerOut-SensorTwo_timerIn);
    speedOut = (baseball_diameter/timePlaneTwo)*milliPerMicro_to_milePreHour;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("V1:");
    lcd.setCursor(0,1);
    lcd.print(speedIn);

    lcd.setCursor(6,0);
    lcd.print("V2:");
    lcd.setCursor(6,1);
    lcd.print(speedOut);

    COR=speedOut/speedIn;
    lcd.setCursor(12,0);
    lcd.print("COR:");
    lcd.setCursor(12,1);
    lcd.print(COR);
    while (COR!=0){}
  }
}
