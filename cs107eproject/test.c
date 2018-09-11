#include "gpio.h"
#include "timer.h"
#include "neopixels.h"

void main(void) {
	//test();   
	ledsetup(); 
	
	/*
	while (1) {   
		showColorNumber(0, 0, 0, 0); 
		timer_delay(1); 
		showColorNumber(255, 0, 0, 5);  
		timer_delay(2);  
		showColorNumber(0, 255, 0, 7); 
		timer_delay(2); 
		showColorNumber(0, 0, 255, 3);  
		timer_delay(2); 
		showColor(255, 0, 0); 
		timer_delay(2); 
		showColor(0, 255, 0); 
		timer_delay(2);
		showColor(0, 0, 255); 
		timer_delay(2);
		showGivenColor(RED); 
		timer_delay(2); 
	}
	*/
	test(); /*
	
	while (1) {
		showColor(0, 0, 0); 
		timer_delay_ms(100); 
		showGivenColorNumber (RED, 1); 
		timer_delay_ms(100); 
		showGivenColorNumber (YELLOW, 2); 
		timer_delay_ms(100); 
		showGivenColorNumber (AMBER, 3); 
		timer_delay_ms(100); 
		showGivenColorNumber (GREEN, 4); 
		timer_delay_ms(100); 
		showGivenColorNumber (CYAN, 5); 
		timer_delay_ms(100); 
		showGivenColorNumber (BLUE, 5); 
		timer_delay_ms(100); 
		showGivenColorNumber (MAGENTA, 6); 
		timer_delay_ms(100); 
		showGivenColorNumber (AMBER, 7); 
		timer_delay_ms(100); 
		showGivenColorNumber (YELLOW, 8); 
		timer_delay_ms(100); 	
		showGivenColorNumber (GREEN, 9); 
		timer_delay_ms(100); 
		showGivenColorNumber (AMBER, 10); 
		timer_delay_ms(100); 
		
	}
	
	while (1) {
		showColor(0, 0, 0); 
		timer_delay_ms(100); 
		showGivenColorNumber(CYAN, 5); 
		//showColorNumber (0, 255, 255, 5); 
		timer_delay(1); 
	}
	
	//run(); 
	//test(); 
	//sendPixel(255, 0, 0);
	//colorWipe(255, 0, 0, 2);  
	*/
}