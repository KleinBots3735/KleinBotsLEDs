//https://github.com/FastLED/FastLED
//https://github.com/FastLED/FastLED/wiki/Overview

#include "FastLED.h"

#define NUM_LEDS 80
CRGB leds[NUM_LEDS];

#define DATA_PIN 3 //Green wire from LEDs
#define CLOCK_PIN 4 //Blue wire from LEDs

#define MAX_BRIGHTNESS 255

void setup()
{
	FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

	// FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop()
{
	//This is kind of Arduino's equivalent to Main() in a standard C program
	//This, as the name implies, loops endlessly.
	//https://code.google.com/p/fastspi/wiki/CRGBreference
	//CSK 3/20/2014 I added a rainbow function just for grins
	rainbow(20);
	cylon(CRGB::Red,25, 5);
	color_chase(CRGB::Green, 15);
	color_chase(CRGB::BlueViolet, 15);
	color_chase(CRGB::Red, 15);
	color_chase(CRGB::Yellow, 15);
	color_chase(CRGB::Green, 15);
	color_chase(CRGB::Cyan, 15);
	color_chase(CRGB::Blue, 15);
	missing_dot_chase(CRGB::White, 20);
	missing_dot_chase(CRGB::Red, 20);
	missing_dot_chase(CRGB::Yellow, 20);
	missing_dot_chase(CRGB::Green, 20);
	missing_dot_chase(CRGB::Cyan, 20);
	missing_dot_chase(CRGB::Blue, 20);
	missing_dot_chase(0x3000cc, 20) ;
}

//These are the functions we have defined to do chase patterns.  They are actually called inside the  loop() above
//They are meant to demonstrate things such as setting LED colors, controlling brightness
void color_chase(uint32_t color, uint8_t wait)
{
	//clear() turns all LEDs off
	FastLED.clear();
	//The brightness ranges from 0-255
	//Sets brightness for all LEDS at once
	FastLED.setBrightness(MAX_BRIGHTNESS);
	// Move a single led
	for(int led_number = 0; led_number < NUM_LEDS; led_number++)
	{
		// Turn our current led ON, then show the leds
		leds[led_number] = color;

		// Show the leds (only one of which is has a color set, from above
		// Show turns actually turns on the LEDs
		FastLED.show();

		// Wait a little bit
		delay(wait);

		// Turn our current led back to black for the next loop around
		leds[led_number] = CRGB::Black;
	}
	return;
}

//Move an "empty" dot down the strip
void missing_dot_chase(uint32_t color, uint8_t wait)
{
	//Step thru some brightness levels from max to 10.  led_brightness/=2 is a cryptic shorthand way of saying led_brightness = led_brightness/2
	for (int led_brightness = MAX_BRIGHTNESS; led_brightness > 10; led_brightness/=2)
	{
		FastLED.setBrightness(led_brightness);

		// Start by turning all pixels on:
		//for(int led_number = 0; led_number < NUM_LEDS; led_number++) leds[led_number] = color;
		//https://github.com/FastLED/FastLED/wiki/Controlling-leds
		fill_solid(leds, NUM_LEDS, color);

		// Then display one pixel at a time:
		for(int led_number = 0; led_number < NUM_LEDS; led_number++)
		{
			leds[led_number] =  CRGB::Black; // Set new pixel 'off'
			if( led_number > 0 && led_number < NUM_LEDS)
			{
				leds[led_number-1] = color; // Set previous pixel 'on'
			}
			FastLED.show();
			delay(wait);
		}
	}
	return;
}

//Cylon - LED sweeps back and forth, with the color, delay and number of cycles of your choice 
void cylon(CRGB color, uint16_t wait, uint8_t number_of_cycles)
{
	FastLED.setBrightness(255);
	for (uint8_t times = 0; times<=number_of_cycles; times++)
	{
		// Make it look like one LED is moving in one direction
		for(int led_number = 0; led_number < NUM_LEDS; led_number++)
		{
			//Apply the color that was passed into the function
			leds[led_number] = color;
			//Actually turn on the LED we just set
			FastLED.show();
			// Turn it back off
			leds[led_number] = CRGB::Black;
			// Pause before "going" to next LED
			delay(wait);
		}

		// Now "move" the LED the other direction
		for(int led_number = NUM_LEDS-1; led_number >= 0; led_number--)
		{
			//Apply the color that was passed into the function
			leds[led_number] = color;
			//Actually turn on the LED we just set
			FastLED.show();
			// Turn it back off
			leds[led_number] = CRGB::Black;
			// Pause before "going" to next LED
			delay(wait);
		}
	}
	return;
}

void rainbow(uint8_t wait) 
{

	uint16_t hue;
	FastLED.clear();

	for(hue=10; hue<255*3; hue++) 
	{

		fill_rainbow( &(leds[0]), NUM_LEDS /*led count*/, hue /*starting hue*/);		
		FastLED.show();
		delay(wait);
	}
	return;
}
