// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************** NEOPIXEL STUFF ***********************************/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN    14

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 24

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

/************************ Example Starts Here *******************************/

// digital pin 5
#define LED_PIN1 2
#define LED_PIN2 5
#define LED_PIN3 4

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("digital");

int reading;
int start;
int data;


void setup() {
  
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);  
  pinMode(LED_PIN3, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  digital->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  digital->get();

/************************** NEOPIXEL STUFF START ***********************************/
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {
  reading = data->toInt();
  Serial.println(reading);
 

  if(reading == 1) {
    WheelBlue2();
  }

  if(reading == 2) {
    SparkleBlue(strip.Color(255, 0, 127, 100)); // Blue, 100% brightness
   }

  if(reading == 3) {
    PulseBlue(strip.Color(255, 0, 127, 50)); // Blue, 100% brightness
  }

  if(reading == 4) {
    Serial.println("OFF");
    OFF(strip.Color(0, 0, 0, 0)); // Blue, 100% brightness
  }
  
  else
  OFF(strip.Color(0, 0, 0, 0));
}



//////////////////////////////////SPARKLE//////////////////////////////////////

void SparkleBlue(uint32_t color) {

    for(int b=0; b<4; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 4) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(50);  // Pause for a moment
      

    }


  io.run();
  
  if(reading == 2) {
    SparkleBlue(strip.Color(255, 0, 127, 100)); // Blue, 100% brightness
  }

  if(reading == 3) {
    PulseBlue(strip.Color(255, 0, 127, 50)); // Blue, 100% brightness
  }
  
  if(reading == 1) {
    WheelBlue2();
  }

  if(reading == 4) {
    Serial.println("OFF");
    OFF(strip.Color(0, 0, 0, 0)); // Blue, 100% brightness
  }
    else
  OFF(strip.Color(0, 0, 0, 0));
}

//////////////////////////////////WHEEL2//////////////////////////////////////

void WheelBlue2() {

  for(byte x = 0; x < 20; x++){
    rotatePixels(strip.Color(255, 0, 127, 100));
    delay(30);
  }

  io.run();
  
  if(reading == 2) {
    SparkleBlue(strip.Color(255, 0, 127, 100)); // Blue, 100% brightness
  }

  if(reading == 3) {
    PulseBlue(strip.Color(255, 0, 127, 50)); // Blue, 100% brightness
  }
  
  if(reading == 1) {
    WheelBlue2();
  }
  
  if(reading == 4) {
 //   Serial.println("OFF");
    OFF(strip.Color(0, 0, 0, 0)); // Blue, 100% brightness
  }
    else
  OFF(strip.Color(0, 0, 0, 0));
}


void rotatePixels(uint32_t color){
  static byte currentPos = 0;
  
  if(++currentPos >= LED_COUNT){
    currentPos = 0;
  }

  strip.setPixelColor((currentPos + LED_COUNT - 1) % LED_COUNT, 0);
  strip.setPixelColor((currentPos + LED_COUNT + 0) % LED_COUNT, color);
  strip.setPixelColor((currentPos + LED_COUNT + 1) % LED_COUNT, color);
  strip.setPixelColor((currentPos + LED_COUNT + 2) % LED_COUNT, color);
  strip.setPixelColor((currentPos + LED_COUNT + 3) % LED_COUNT, color);
  strip.show();
}

//////////////////////////////////PULSE//////////////////////////////////////

void PulseBlue(uint32_t color) {

{
  for(int j=50; j<200; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(j, 0, j, 0));
    strip.show();
    delay(5);
  }
  for(int j=200; j>=50; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(j, 0, j, 0));
    strip.show();
    delay(5);
  }
  }

  io.run();
  if(reading == 2) {
     SparkleBlue(strip.Color(255, 0, 127, 100)); // Blue, 100% brightness
  }

  if(reading == 3) {
    PulseBlue(strip.Color(255, 0, 127, 50)); // Blue, 100% brightness
  }
  
  if(reading == 1) {
    WheelBlue2();
  }
  if(reading == 4) {
    Serial.println("OFF");
    OFF(strip.Color(0, 0, 0, 0)); // Blue, 100% brightness
  }
    else
  OFF(strip.Color(0, 0, 0, 0));
}

//////////////////////////////////OFF//////////////////////////////////////

void OFF(uint32_t color) {

    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, 0, 0));
    strip.show();

  io.run();
   if(reading == 2) {
  SparkleBlue(strip.Color(255, 0, 127, 100)); // Blue, 100% brightness
  }

  if(reading == 3) {
    PulseBlue(strip.Color(255, 0, 127, 50)); // Blue, 100% brightness
  }
  
  if(reading == 1) {
    WheelBlue2();
  }
  
  if(reading == 4) {
    Serial.println("OFF");
    OFF(strip.Color(0, 0, 0, 0)); // Blue, 100% brightness
  }
    else
  OFF(strip.Color(0, 0, 0, 0));
}

