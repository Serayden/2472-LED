#include <FastLED.h>

#define LED_PIN_RIGHT 12
#define LED_PIN_LEFT 13
#define NUM_LEDS 24
#define TalonRight 11 //Talon Right Pin
#define TalonLeft 10 //Talong Left Value

int TRV; //Talong Right Value
int TLV; //Talong Left Value
int TRD; //Talon Right Delay
int TLD; //Talon left Dalay

int a; //Right Strip
int b;
int c;
int d;
int e; //Left Strip
int f;
int g;
int h;

CRGB Rleds[NUM_LEDS];
CRGB Lleds[NUM_LEDS];
//defines delays
#define ShortDelay 7 //based off speed of travel on robot
#define LongDelay 200

//defines Color1
#define Color1 Red
#define Color2 Blue

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN_LEFT, GRB>(Lleds, NUM_LEDS) ; //defines the type of led strip
  FastLED.addLeds<WS2812B, LED_PIN_RIGHT, GRB>(Rleds, NUM_LEDS) ; //defines the type of led strip
  Serial.begin(9600);
  pinMode (TalonRight, INPUT);
  a = 0;
  b = 1;
  c = 12;
  d = 13;

  for (int i=0; i <= 23; i++){
    Rleds[i] = CRGB::Color1;
    Lleds[i] = CRGB::Color1;
    FastLED.show();
  }

  Rleds[a] = CRGB::Color2;
  Rleds[b] = CRGB::Color2;
  Rleds[c] = CRGB::Color2;
  Rleds[d] = CRGB::Color2;

  Lleds[e] = CRGB::Color2;
  Lleds[f] = CRGB::Color2;
  Lleds[g] = CRGB::Color2;
  Lleds[h] = CRGB::Color2;

  FastLED.show();
}

void loop() {
  TRV = pulseIn (TalonRight, LOW); //accepts input value from RIO
  if (TRV <= 8420) {
    TRD = map(TRV, 8420, 7540, LongDelay, ShortDelay); //maps values from Rtalon into delays Forward
  }
  if (TRV >= 8450) {
    TRD = map(TRV, 8450, 9380, LongDelay, ShortDelay); //maps values from Rtalon into delays Backward
  }

  //TLV = pulseIn (TalonLeft,LOW); //accepts input value from RIO
  //if (TLV <= 8420) {
  //  TLD = map(TLV, 8420, 7540, LongDelay, ShortDelay); //maps values from Ltalon into delays Forward
  //}
  //if (TLV >= 8450) {
  //  TLD = map(TLV, 8450, 9380, LongDelay, ShortDelay); //maps values from Ltalon into delays Backward
  //}

  if (TRV <= 8400) {    //Forward LED movements
    delay (TRD);
    Rleds[a] = CRGB::Color1;
    Rleds[c] = CRGB::Color1;
    a ++;
    b ++;
    c ++;
    d ++;
    if (a > 23) {
      a = 0;
    }
    if (b > 23) {
      b = 0;
    }
    if (c > 23) {
      c = 0;
    }
    if (d > 23) {
      d = 0;
    }
    Rleds[b] = CRGB::Color2;
    Rleds[d] = CRGB::Color2;
    FastLED.show ();
  }

    if (TRV >= 8470) {    //Reverse LED movements
    delay (TRD);
    Rleds[b] = CRGB::Color1;
    Rleds[d] = CRGB::Color1;
    a --;
    b --;
    c --;
    d --;
    if (a < 0) {
      a = 23;
    }
    if (b < 0) {
      b = 23;
    }
    if (c < 0) {
      c = 23;
    }
    if (d < 0) {
      d = 23;
    }
    Rleds[a] = CRGB::Color2;
    Rleds[c] = CRGB::Color2;
    FastLED.show ();

  }
  //


}
