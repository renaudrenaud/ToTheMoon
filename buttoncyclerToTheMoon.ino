// Simple demonstration on using an input device to trigger changes on your
// NeoPixels. Wire a momentary push button to connect from ground to a
// digital IO pin. When the button is pressed it will change to a new pixel
// animation. Initial state has all pixels off -- press the button once to
// start the first animation. As written, the button does not interrupt an
// animation in-progress, it works only when idle.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Digital IO pin connected to the button. This will be driven with a
// pull-up resistor so the switch pulls the pin to ground momentarily.
// On a high -> low transition the button press logic will execute.
#define BUTTON_PIN   2

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 24  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

boolean oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-9
boolean lightOn;
boolean ButtonPressed = false; 

void setup() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);  // Start serial monitor after a few seconds. Mainly for testing code to get it to work.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
  lightOn = false;
  pinMode(LED_BUILTIN, OUTPUT);
  colorWipe(strip.Color( 0,  0,  0), 50);    // black to start
  delay (2000); //tempo before attaching the interrupt
  attachInterrupt(digitalPinToInterrupt(2), changeMode, LOW);  // button is set to interrupt mode
  digitalWrite(LED_BUILTIN, LOW);

}

void changeMode() {
   
    detachInterrupt(digitalPinToInterrupt(2));  // button is detached from interrupt mode
    Serial.print("interruption active ");  // Prints "Mode" to serial monitor. Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
    ButtonPressed = true;  // to test within the main function in order to exit
    Serial.print("Button by ChangeMode");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.

     // some LED activity for visual debug
      // if (lightOn) {
      //   digitalWrite(LED_BUILTIN, HIGH);
      //  lightOn = false;
      //} else {
      //  digitalWrite(LED_BUILTIN, LOW);
      //  lightOn = true;
      // }

      // put the lights to Blue to signal that it memorised the change
      colorWipeUniterrupted(strip.Color(  0,   0,   127), 10);    // blue quick
      //strip.fill(strip.Color(  0,   0,   127));
      //delay(500);
      mode = mode + 1 ;
    Serial.print("Mode dans interruption");  // Prints "Mode" to serial monitor. Mainly for troubleshooting.
    Serial.print(mode);
    Serial.print('\n');  // Prints the speed to the serial monitor. Mainly for troubleshooting.
      
      if(mode > 8) mode = 0; // Advance to next mode, wrap around after #8
//    }
//      // Set the last-read button state to the old state.
//  oldState = newState;
//  }
    Serial.print("interruption inactive ");  // Prints "Mode" to serial monitor. Mainly for troubleshooting.
    Serial.print('\n');  // Prints the speed to the serial monitor. Mainly for troubleshooting.  
    attachInterrupt(digitalPinToInterrupt(2), changeMode, LOW);  // button is set to interrupt mode
}

void loop() {  
  //  run the selected mode animation
    Serial.print("Mode dans loop ");  // Prints "Mode" to serial monitor. Mainly for troubleshooting.
    Serial.print(mode);
    Serial.print('\n');  // Prints the speed to the serial monitor. Mainly for troubleshooting.
  switch(mode) {           // Start the new animation...
    
    case 0:
      colorWipe(strip.Color( 0,  0,  0), 50);    // black
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case 1:
      digitalWrite(LED_BUILTIN, HIGH);
      colorWipe(strip.Color(  0,   0,   0), 200);    // Black/off
      colorWipe(strip.Color( 10,   0,   0), 200);    // Red
      colorWipe(strip.Color(100,   0,   0), 200);    // Red
      colorWipe(strip.Color(255,   0,   0), 200);    // Red
      colorWipe(strip.Color(100,   0,   0), 200);    // Red
      colorWipe(strip.Color( 50,   0,   0), 200);    // Red
      break;
    case 2:
      HueIntens(0, 10);          // red Hue
      break;
    case 3:
      colorWipe(strip.Color(  180, 100,   0), 50);    // orange
      colorWipe(strip.Color(  127, 127, 127), 50);    // white
      colorWipe(strip.Color(  200, 200,    0), 50);    // yellow
      colorWipe(strip.Color(  255, 128,   0), 50);    // orange
      colorWipe(strip.Color(  100,   0,   0), 50);    // Red
      break;
    case 4:
      colorWipe(strip.Color(   30,  30,  30), 50);    // white
      colorWipe(strip.Color(  127, 127, 127), 50);    // white
      colorWipe(strip.Color(  255, 255, 255), 50);    // 
      colorWipe(strip.Color(  127, 127, 127), 50);    // 
      colorWipe(strip.Color(    0,   0,   0), 50);    // black
      break;
    case 5:
      HueIntens(65536/6, 10);    // Yellow Hue
      break;
    case 6:
      colorWipe(strip.Color(  30,   30,   30), 200);    // white 
      break;
    case 7:
      rainbow(20);
      break;
    case 8:
      theaterChaseRainbow(50);
      break;
      }
     
      ButtonPressed = false; //
    Serial.print("Button by loop");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
    if(ButtonPressed) {
     //  ButtonPressed=false;
    Serial.print("Button by colorWipe");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
       break;
       }
  }
}

void colorFlash(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    if(ButtonPressed) {
      // ButtonPressed=false;
    Serial.print("Button by colorFlash");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
       break;
       }
  }
  delay(wait);                           //  Pause for a moment
}


// faire varier l'intensit?? de la couleur demand??e de mini ?? maxi puis revient ?? mini
void HueIntens(int Hue,  int wait) {
  int x = 1;
  for(int i = 0; i > -1 ; i = i + x) { // For each level of brightness
    strip.fill(strip.gamma32(strip.ColorHSV(Hue,127,i)));         
    strip.show();                          //  Update strip to match
    if (i == 255) {
      x = -1;  // switch direction at peak
    }
    if(ButtonPressed) {
     //  ButtonPressed=false;
    Serial.print("Button by HueIntens");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
       break;
       }
  delay(wait);                           //  Pause for a moment
  }
}
void colorWipeUniterrupted(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
    if(ButtonPressed) {
     //  ButtonPressed=false;
    Serial.print("Button by theaterChase");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
       break;
       }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    if(ButtonPressed) {
    //  ButtonPressed=false;
    Serial.print("Button by rainbow");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
      break;
      }
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
    if(ButtonPressed) {
    //  ButtonPressed=false;
    Serial.print("ButtonPressed by theaterChaseRainbow");  //  Mainly for troubleshooting.
    Serial.print(ButtonPressed);  //  Mainly for troubleshooting.
    Serial.print('\n');  //  Mainly for troubleshooting.
      break;
      }
  }
}
