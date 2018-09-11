/*
 This source code has been adapted from the Arduino code @ http://wp.josh.com/2014/05/11/ws2812-neopixels-made-easy/
*/

#include "gpio.h"
#include "timer.h"
#include "armtimer.h"
#include "malloc.h"
#include "neopixels.h"
#include "stdio.h"

// Change this to be at least as long as your pixel string (too long will work fine, just be a little slower)

#define PIXELS 10  // Number of pixels in the string

#define PIN GPIO_PIN18 

// Here are some convience defines for using nanoseconds specs to generate actual CPU delays

int colors[] = {BLACK, WHITE, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, AMBER}; 

// Actually send a bit to the string. We must to drop to asm to enusre that the complier does
// not reorder things and make it so the delay happens in the wrong place.

inline void sendBit( bool bitVal ) {
  
    if (  bitVal ) {				// 1 bit
    
    		*GPIO_REG_SET0 = 0x1<<PIN; 
	    
		__asm__ volatile ( //each asm nop instruction takes around 9.15 nanoseconds -- I need the T1H to be 800 nanoseconds so I call the 87 times
		
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			

			
			//"#1: \n\t" 
			//"#subs r1, r1, #1\n\t"
			//"#bne 1b\n\t"
		
			
		);
		
		*GPIO_REG_CLR0 = 0x1<<PIN;  
		
		__asm__ volatile ( // T1L needs to be around 450 nanoseconds so I call nop around 49 times
		
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			

			//"#2: \n\t" 
			//"#subs r1, r1, #1\n\t"
			//"#bne 2b\n\t"
		

		
		);
                                  
    }
     else {					// 0 bit

		// **************************************************************************
		// This line is really the only tight goldilocks timing in the whole program!
		// **************************************************************************


		*GPIO_REG_SET0 = 0x1<<PIN; 
		
		__asm__ volatile ( //TOH needs to be 400 nanoseconds so I need to call nop 44 times 
		
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			

			
			//"#3: \n\t" 
			//"#subs r1, r1, #1\n\t"
			//"#bne 3b\n\t"
		);
      
      	*GPIO_REG_CLR0 = 0x1<<PIN;  
      	
      	__asm__ volatile ( //T0L needs to be 850 nanoseconds so I need to call nop 93 times
		
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
			"mov r1, r1\n\t"
		
		);
      
    }
    
    // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the 5us reset timeout (which is A long time)
    // Here I have been generous and not tried to squeeze the gap tight but instead erred on the side of lots of extra time.
    // This has thenice side effect of avoid glitches on very long strings becuase 

    
}  

// sendByte function basically calls sendBit for the last bit and then left shifts everything once so that it sends out the bits from highest
// to lowest 
inline void sendByte( unsigned char byte ) {
    
    for( unsigned char bit = 0 ; bit < 8 ; bit++ ) {
      
      sendBit( bitRead( byte , 7 ) );                // Neopixel wants bit in highest-to-lowest order
                                                     // so send highest bit (bit #7 in an 8-bit byte since they start at 0)
      byte <<= 1;                                    // and then shift left so bit 6 moves into 7, 5 moves into 6, etc
      
    }           
} 

/*
  The following three functions are the public API:
  
  ledSetup() - set up the pin that is connected to the string. Call once at the begining of the program.  
  sendPixel( r g , b ) - send a single pixel to the string. Call this once for each pixel in a frame.
  show() - show the recently sent pixel on the LEDs . Call once per frame. 
  
*/


// Set the specified pin up as digital out

void ledsetup() {
  
  bitSet( PIXEL_DDR , PIXEL_BIT );
  
}

// sendPixel calls sendByte 3 times for green first then red and blue 
inline void sendPixel( unsigned char r, unsigned char g , unsigned char b )  {  
  
  sendByte(g);          // Neopixel wants colors in green then red then blue order
  sendByte(r);
  sendByte(b);
  
}


// Just wait long enough without sending any bots to cause the pixels to latch and display the last sent frame

inline void show() {
	timer_delay_us(6); 
}

// this asm_test is a simple loop that I was trying to use in order to find out how long in nanoseconds each asm step took because the pi can't measure
// in nanoseconds using the timer.h 
inline void asm_test (void) {
	__asm__ volatile( 
		"#mov r1, #1000\n\t"
		"runthrough: \n\t"
		"subs r1, r1, #1\n\t"
		"bne runthrough\n\t"		
	);
}


//this test function acted as a public wrapper for all of the other inline code that I needed to try testing 
//there's a lot of commented out portions that I left in this finished version because I thought it was worthwhile showing how I went about 
//testing different aspects 
void test (void) {
	//unsigned char input = 185; 
	//sendByte(input);
	//printf("here"); 
	//sendPixel(0, 0, 0); 
	//show();
	
	//show(); 
	//printf("finished"); 
	while( 1) {
		showColor(0, 0, 0); //shows a zero for everything 
		showColor(0, 0, 0); 
		showColor(0, 0, 0); 
		showColor(0, 0, 0); 
		timer_delay_ms(100); 
		showColorNumber(255, 0, 0, 2); //this fills up the 2 red pixels for each of the 4 led strips 
		showColorNumber(255, 0, 0, 2); 
		showColorNumber(255, 0, 0, 2); 
		showColorNumber(255, 0, 0, 2); 
		timer_delay_ms(200); 
		show(); 
		showColorNumber(0, 255, 0, 3); // same but 3 green pixels 
		showColorNumber(0, 255, 0, 3);
		showColorNumber(0, 255, 0, 3);
		showColorNumber(0, 255, 0, 3);
		timer_delay_ms(200); 
		show(); 
		showColorNumber(0, 255, 0, 5); // same but 5 green pixels 
		showColorNumber(0, 255, 0, 5);
		showColorNumber(0, 255, 0, 5);
		showColorNumber(0, 255, 0, 5);
		timer_delay_ms(200); 
		show();
		showColorNumber(0, 255, 255, 8); // eight pixels 
		showColorNumber(0, 255, 255, 8);
		showColorNumber(0, 255, 255, 8);
		showColorNumber(0, 255, 255, 8);
		timer_delay_ms(200); 
		show();
	}

	//sendPixel(0, 0, 255);
	//sendPixel(0, 255, 0);
	
	

	//showColor(255, , 0); 
	 
	//showColor(0, 0, 255); 
	//show(); 
	//sendPixel(0, 0, 255); 
	//sendPixel(255, 0, 0); 
	show(); 
	//sendPixel(255, 0, 0); 
	//sendPixel(255, 0, 0); 
	//show(); 
	//unsigned int start; 
	//unsigned int end; 
	
	
	//start = timer_get_ticks(); 
	/*
	__asm__ volatile( 
		"#mov r1, #50;"
		"loop: ;"
		"subs r1, #1;"
		"bne loop;"		
	);
	*/
	/*
	asm_test(); 
	end = timer_get_ticks(); 
	printf("end = %d and start = %d the time it takes for one arm instruction = %d\n", end, start, end - start); 
	
	
	unsigned int start = timer_get_ticks(); 
	gpio_write(PIN, 0x1); 
	unsigned int end = timer_get_ticks(); 
	printf("writing 0x1 takes %d microseconds\n", end - start); 
	start = timer_get_ticks(); 
	gpio_write(PIN, 0x0); 
	end = timer_get_ticks(); 
	printf("writing 0x0 takes %d microseconds\n", end - start); 
	unsigned int output = (int)bitRead(1001, 3); 
	printf("bit = %d\n", output); 
	start = timer_get_ticks(); 
	asm_test(); 
	end = timer_get_ticks(); 
	printf("one asm instruction takes around %d microseconds\n", (end - start) ); 
	*/
}


/*
  That is the whole API. What follows are some demo functions rewriten from the AdaFruit strandtest code...
  
  https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest/strandtest.ino
  
  Note that we always turn off interrupts while we are sending pixels becuase an interupt
  could happen just when we were in the middle of somehting time sensitive.
  
  If we wanted to minimize the time interrupts were off, we could instead 
  could get away with only turning off interrupts just for the very brief moment 
  when we are actually sending a 0 bit (~1us), as long as we were sure that the total time 
  taken by any interrupts + the time in our pixel generation code never exceeded the reset time (5us).
  
*/

void separateColor (unsigned int color, unsigned char* r, unsigned char* g, unsigned char* b) {
	*r = (color & 0xff<<16) >> 16; 
	*g = (color & 0xff<<8) >> 8;  
	*b = (color & 0xff);  
}

// Display a single color on the whole string - these have been adapted to not show at the end because you need to call it four times 
// to fill up the 40 pixels which was necessary for the demo 

void showColor( unsigned char r , unsigned char g , unsigned char b ) {

  for( int p=0; p<PIXELS; p++ ) {
    sendPixel( r , g , b );
  }

  
}

// Display a single color on the string until a certain point - removed the show

void showColorNumber( unsigned char r , unsigned char g , unsigned char b , unsigned int count) {
  if (count > PIXELS) return; 

  unsigned int p = 0;  
  for (p = 0; p < count; p++) {
  	sendPixel( r, g, b); 
  }
  for (p = count; p <= PIXELS; p++) {
  	sendPixel( 0, 0, 0); 
  }

  
}

// this function is the same as below except that it only turns on the certain number of leds 
void showGivenColorNumber (unsigned int color, unsigned int number) {
	unsigned char* r = malloc(1); 
	unsigned char* g = malloc(1); 
	unsigned char* b = malloc(1); 
	separateColor(color, r, g, b); 
	showColorNumber(*r, *g, *b, number);  
}

// this function takes in a color that's type unsigned int and then it'll separate them into rgb values and call showColor()
void showGivenColor (unsigned int color) {
	unsigned char * r = malloc(1); 
	unsigned char* g = malloc(1); 
	unsigned char* b = malloc(1); 
	separateColor(color, r, g, b); 
	showColor(*r, *g, *b); 
}

// we were trying to use this in our audio.c file so that we could light up the pixels depending on the amplititude of the function 
void frame (int pixels_light) {
	showGivenColorNumber (RED, pixels_light); 
	show(); 
}



void setup() {
    
  ledsetup();  
  
}


