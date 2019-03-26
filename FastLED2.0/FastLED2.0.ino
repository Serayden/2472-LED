#include <FastLED.h>

#define LED_PIN 13
#define NUM_LEDS 24
#define Talon 11 //Talon Pin
#define Button_Pin 10


int TV; //Talong Value
int TD; //Talon Delay

int P0;   //for freestyle led
int P49;  //revers lower limit
int P50;  //for reverse max power
int P99;  //for reverse low power
int P101; //for forward low power
int P150; //for forward max power
int P151; //forward upper limit
int P200; //for climb 200+


int a; //Right Strip
int b;
int c;
int d;
int e;
int f;

CRGB leds[NUM_LEDS];

//defines delay
#define ShortDelay 7 //based off speed of travel on robot
#define LongDelay 200

//defines Color1
int Color1;
int Color2;
#define Red 255, 0, 0
#define Blue 0, 0, 255

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS) ; //defines the type of led strip
  Serial.begin(9600);
  pinMode (Talon, INPUT);
  pinMode (Button_Pin, INPUT_PULLUP);
  int Button = digitalRead(Button_Pin);
  if (Button == HIGH) {
    Color1 = Red;
    Color2 = Blue;
  }
  else {
    Color1 = Blue;
    Color2 = Red;
  }

  a = 0;
  b = 1;
  c = 12;
  d = 13;

  for (int i = 0; i <= 23; i++) {
    leds[i] = CRGB(Color1);
    FastLED.show();
  }

  //  leds[a] = CRGB(Color2);
  //  leds[b] = CRGB(Color2);
  //  leds[c] = CRGB(Color2);
  //  leds[d] = CRGB(Color2);
  //  FastLED.show();
}

void loop() {
  int Button = digitalRead(Button_Pin);
  if (Button == HIGH) {
    Color1 = Red;
    Color2 = Blue;
  }
  else {
    Color1 = Blue;
    Color2 = Red;
  }

  TV = pulseIn (Talon, LOW); //accepts input value from RIO
  if (TV <= P101 && TV >= P150) {
    TD = map(TV, P101, P150, LongDelay, ShortDelay); //maps values from Rtalon into delays Forward
  }
  if (TV >= P99 && TV <= P50) {
    TD = map(TV, P50, P99, LongDelay, ShortDelay); //maps values from Rtalon into delays Backward
  }



  if (TV <= P49 && TV >= P151) {     //for driving movement
    leds[a] = CRGB(Color2);
    leds[b] = CRGB(Color2);
    leds[c] = CRGB(Color2);
    leds[d] = CRGB(Color2);
    FastLED.show();
    
    if (TV <= P101) {    //Forward LED movements
      delay (TD);
      leds[a] = CRGB(Color1);
      leds[c] = CRGB(Color1);
      b ++;
      c ++;
      a ++;
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
        return;
      }
      leds[b] = CRGB(Color2);
      leds[d] = CRGB(Color2);
      FastLED.show ();
    }

    if (TV >= P99) {    //Reverse LED movements
      delay (TD);
      leds[b] = CRGB(Color1);
      leds[d] = CRGB(Color1);
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
        return;
      }
      leds[a] = CRGB(Color2);
      leds[c] = CRGB(Color2);
      FastLED.show ();
    }


  }
}
