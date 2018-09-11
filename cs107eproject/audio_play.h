#include "timer.h"
#include "gpio.h"
#include "pwm.h"
#include "audio.h"
#include "gpioextra.h"
#include "interrupts.h"
#include "assert.h"
#include "uart.h"
#include "debounce.h"

void button_handler(unsigned int pc);
void audio_play_init();

// void setup_interrupts(void);