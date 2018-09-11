#ifndef NEOPIXELS_H
#define NEOPIXELS_H 

// These are the timing constraints taken mostly from the WS2812 datasheets 
// These are chosen to be conservative and avoid problems rather than for maximum throughput 

#define T1H  900    // Width of a 1 bit in ns
#define T1L  600    // Width of a 1 bit in ns

#define T0H  400    // Width of a 0 bit in ns
#define T0L  900    // Width of a 0 bit in ns

#define RES 6000    // Width of the low gap between bits to cause a frame to latch

// Here are some convience defines for using nanoseconds specs to generate actual CPU delays

#define NS_PER_SEC (1000000000L)          // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives

#define CYCLES_PER_SEC (F_CPU)

#define NS_PER_CYCLE ( NS_PER_SEC / CYCLES_PER_SEC )

#define NS_TO_CYCLES(n) ( (n) / NS_PER_CYCLE )

#define BLACK   0xFF000000
#define WHITE   0xFFFFFFFF
#define RED     0xFFFF0000
#define GREEN   0xFF00FF00
#define BLUE    0xFF0000FF
#define CYAN    0xFF00FFFF
#define MAGENTA 0xFFFF00FF
#define YELLOW  0xFFFFFF00
#define AMBER   0xFFFFBF00


// Actually send a bit to the string. We must to drop to asm to enusre that the complier does
// not reorder things and make it so the delay happens in the wrong place.

inline void sendBit (unsigned char bitVal); 

// Read the bit at the given position of the number 

inline unsigned char bitRead(unsigned char number, unsigned int position);

// Send the byte given to the specified GPIO pin

inline void sendByte(unsigned char byte); 

// the following are the public functions used to actually display things 

// Sets the GPIO pin to output. Call at the beginning of the program 

void ledsetup(); 

// Sends the pixel to the GPIO pin and down the line. Call this once for each pixel in a frame 

inline void sendPixel(unsigned char r, unsigned char g, unsigned char b); 

// Displays the frame by causing a delay

inline void show(); 

void test(); 

void frame(int pixels_light); 

void separateColor (unsigned int color, unsigned char* r, unsigned char* g, unsigned char* b);

void showGivenColorNumber (unsigned int color, unsigned int number); 

void showGivenColor (unsigned int color);  

void showColor( unsigned char r, unsigned char g, unsigned char b ); 

void showColorNUmber( unsigned char r, unsigned g, unsigned char b, unsigned int count); 

void colorWipe( unsigned char r, unsigned char g, unsigned char b, unsigned char wait); 

void theaterChase( unsigned char r, unsigned char g, unsigned char b, unsigned char wait); 

void rainbowCycle( unsigned char frames, unsigned int frameAdvance, unsigned int pixelAdvance); 

void detonate (unsigned char r, unsigned char g, unsigned char b, unsigned int startdelayms); 

void run(); 

void setup(); 

/*
			"sbi %[port], %[bit] \n\t"				// Set the output bit
			".rept %[onCycles] \n\t"                                // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t"
			"cbi %[port], %[bit] \n\t"                              // Clear the output bit
			".rept %[offCycles] \n\t"                               // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t"
			::
			[port]		"I" (_SFR_IO_ADDR(PIXEL_PORT)),
			[bit]		"I" (PIXEL_BIT),
			[onCycles]	"I" (NS_TO_CYCLES(T1H) - 2),		// 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work
			[offCycles] 	"I" (NS_TO_CYCLES(T1L) - 2)			// Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness
			*/ 

#endif