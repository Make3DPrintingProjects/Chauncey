//WrylonRoboticalFlowerBot2.ino
////////////////////////////////////////////////////////////////////////////
//-+ Welcome to the Wrylon Robotical Flower Care Robot Arduino sketch! +-
//     This program is used to imbue Chauncey, the Wrylon Robotical Flower Care Robot with 
//     the latest in flower care intelligence. Simply wire up the circuit, 
//     power up the bot, fill the watering can with water, and enjoy 
//     effortless care of your prized flower.
//
//
// by John Edgar Park (with optimization notes by Ronan Park)
//           The web: www.jpixl.net
//           The mail: jp@jpixl.net 
//           The twitter: @johnedgarpark
//
////////////////////////////////////////////////////////////////////////////
// Software:  Arduino 1.6.5 (or later)
// Hardware:  Arduino Uno (or equivalent)
//            Adafruit Industries Motor Shield v2
//            DC motor
//            10mm red LED
//            10mm green LED
//            10k resistor (x2)
//            220ohm resistor
//            1/8" O.D. 12" length brass tube (x2) (or two stainless steel nails or bolts or screws) with wires soldered to them as moisture sensor probes
//            Stranded wire for circuit hookup
//            WingShield Industries ScrewShield (optional) for connecting the wiring to the Arduino and Motor Shield
//            4 AA battery supply (or wall wart) for powering the Arduino
//            Proper battery (or wall wart) for powering the motor (e.g., 7.2V 1500mAh NiMH RC car battery)
//
////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_MotorShield.h> 
//Include the Adafruit Motor Library (found here: https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-software )
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address
Adafruit_DCMotor *motor3 = AFMS.getMotor(3); //We'll use the third motor output on the Motor Shield, so be sure to wire the motor to the to M3 terminal block outputs.

int moistPin = 0; //The analog A0 pin on the Arduino will test the resistance of the probe
int moistValue; //variable to hold resistance read from moistPin.
int powerLEDPin = 12;//10mm green LED with 10K resistor will 
int alertLEDPin = 9;//10mm red LED with 220ohm resistor
int dryValue = 560;//calibrated value for moisture. typical value of 650 to 750 for 30% water to soil mix. Change this value to adjust how dry the soil is before it is watered.
int motorRunValue = 8000; //motor run time in milliseconds, 8000 millis (8 seconds) default
int motorSpeed = 225; //change this value to speed up or slow down the motor rate. Range is 0-255.
//initialize variables to store readings from sensor
int moistVal = 0;

void setup(){

  pinMode(powerLEDPin, OUTPUT);  //set LED pin modes to output
  pinMode(alertLEDPin, OUTPUT);  //set LED pin modes to output
  digitalWrite(powerLEDPin, HIGH);  //light the power LED
  digitalWrite(alertLEDPin, LOW);  //make sure the alert LED is off
  AFMS.begin(1000);
  motor3->setSpeed(motorSpeed);  //set motor at full power
  motor3->run(RELEASE);  //make sure motor is disengaged.
  Serial.begin(9600);  //initialize the serial port for output to the serial monitor for testing
  Serial.println();
  Serial.println();
  Serial.println("----- WRYLON ROBOTICAL Flower Bot -----");
  Serial.println();
  Serial.println("----- Boot sequence complete. -----");
  Serial.println();
  Serial.println();

}

void loop(){

  moistVal = analogRead(moistPin);  //read the moisture probes

  //write moisture values to serial port
  Serial.print("Wrylon Robotical Soil Moisture Level Probe currently detects a level of:   ");
  Serial.println(moistVal);
  delay(2000);  //how often to check moisture level in milliseconds

  //run alert and motor if mosture level is too low
  //note, you can adjust this value to suit your flower, a higher value means that the soil is kept more moist
  //typical values are around 750 for 30% water to soil 
  //lower than dryValue means it's time to water the flower
  if(moistVal>=dryValue){
      Serial.println("     Your flower appears to be in an ideally moist environment.");
      Serial.print("      (I will endevour to keep the moisture level above: ");
      Serial.print(dryValue);
      Serial.println(")");
      Serial.println();

    digitalWrite(alertLEDPin, LOW); //since the moisture level is above the dry value, turn off (or keep turned off) the red alert LED
    //delay(150); 

  }
  else{

    digitalWrite(alertLEDPin, HIGH);    //it's too dry, light the alert LED! Keep it lit until watered
    
    Serial.println();
    Serial.println("Oh dear! The soil level has dropped below the acceptable level. Watering shall now commence.");
    Serial.println();
    
    motor3->run(FORWARD);   //set the motor running in the forward direction ("forward" is relative, you may change value to BACKWARD if the motor runs in the wrong direction to engage the watering can mechanism.)
    delay(motorRunValue);  //run the motor for the number of milliseconds set at the top of the sketch
    motor3->run(RELEASE);   //stop the motor
    
    Serial.println("Watering has completed, moisture should soon return to an acceptable level.");
    Serial.println();
    Serial.println();
  }
}
// end WrylonRoboticalFlowerBot2.ino
////////////////////////////////////////////////////////////////////////////
