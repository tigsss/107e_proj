#include "timer.h"
#include "gpio.h"
#include "pwm.h"
#include "audio.h"
#include "gpioextra.h"
#include "interrupts.h"
#include "assert.h"
#include "uart.h"
#include "ringbuffer.h"
#include "debounce.h"

static int PAUSE = GPIO_PIN25;
static int SKIP = GPIO_PIN23;
static int REWIND = GPIO_PIN24;
//23 white
// 24 orange


volatile extern int pause;
volatile extern int skip;
volatile extern int rewind;

int begin;
int end;
void button_handler(unsigned int pc) {
	end = timer_get_ticks();
	if (end - begin < 200000)
	{
        // Button debouncing
	}
    else if (gpio_check_event(PAUSE) == 1)
    {
        pause = pause ^ 1;
        begin = timer_get_ticks();
    }
    else if (gpio_check_event(SKIP) == 1)
    {
        skip = 1;
        
        begin = timer_get_ticks();
    }
    else if (gpio_check_event(REWIND) == 1)
    {
        rewind = 1;
        
        begin = timer_get_ticks();
    }

    gpio_clear_event(PAUSE);
    gpio_clear_event(SKIP);
    gpio_clear_event(REWIND);
}

void audio_play_init()
{    
	gpio_init();
    uart_init();

	gpio_set_input(PAUSE);
    gpio_set_pullup(PAUSE);

    gpio_set_input(SKIP);
    gpio_set_pullup(SKIP);

    gpio_set_input(REWIND);
    gpio_set_pullup(REWIND);

    begin = timer_get_ticks();

    gpio_enable_event_detection(PAUSE, GPIO_DETECT_FALLING_EDGE);
    gpio_enable_event_detection(SKIP, GPIO_DETECT_FALLING_EDGE);
    gpio_enable_event_detection(REWIND, GPIO_DETECT_FALLING_EDGE);

    bool ok = interrupts_attach_handler(button_handler);
    assert(ok);
    interrupts_enable_source(INTERRUPTS_GPIO3);
    interrupts_global_enable();

    pause = 0;
    skip = 0;
    rewind = 0;

	timer_init();
	gpio_init();
	uart_init();
    gpio_set_function( 40, GPIO_FUNC_ALT0 ); // PWM0
    gpio_set_function( 45, GPIO_FUNC_ALT0 ); // PWM1
    gpio_set_function( 18, GPIO_FUNC_ALT5 ); // PWM0

    audio_init();
}



