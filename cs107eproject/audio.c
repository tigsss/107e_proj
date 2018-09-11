#include <stdint.h>
#include "timer.h"
#include "gpio.h"
#include "pwm.h"
#include "malloc.h"
#include "audio.h"
#include <math.h>
#include "neopixels.h"

// Initializes for the correct frequences of 44.1kHz

#define FREQ (19200000/2)
#define HZ 44100
#define M_PI 3.14159265358979

void compute_dft_real_pair(uint16_t inreal[], uint16_t out[], int n);

/*
   Initialize the pwm for audio.

   - base clock is 9600000
   - pwm range is 256  for a sample clock rate of 37500 Khz
   - writing a 256 sample waveform will repeat sound at 37500/256 = 146.5 Hz
*/
void audio_init(void) 
{
    gpio_set_function( 40, GPIO_FUNC_ALT0 );
    gpio_set_function( 45, GPIO_FUNC_ALT0 );
    timer_delay_ms(2);

    pwm_init();

    pwm_set_clock( FREQ ); // 9600000 Hz
    timer_delay_ms(2);

    // pwm_set_mode( 0, PWM_SIGMADELTA ); 
    // pwm_set_mode( 1, PWM_SIGMADELTA );

    pwm_set_mode( 0, PWM_MARKSPACE);
    pwm_set_mode( 1, PWM_MARKSPACE);

    pwm_set_fifo( 0, 1 ); 
    pwm_set_fifo( 1, 1 );

    pwm_enable( 0 ); 
    pwm_enable( 1 );

    int width = FREQ/HZ;
    pwm_set_range( 0, width );
    pwm_set_width( 0, width/4 );
    pwm_set_range( 1, width );
    pwm_set_width( 1, width/4 );
    // printf("width: %d", width);

    timer_delay_ms(2);
}

/* 
   These functions transmit a wave to the RPi audio jack 
   as a pulse-width-modulated signal.
   
   The waveform array contains 256 entries.

   There are 3 functions depending on the type of the
   waveform array: u8, u16, i16.

   phase is a 32-bit quantity. The upper 8-bits are used as an
   index into the wavefrom array and selects one of the 256 samples.
   
   dphase is added to phase after each sample is output.  

   Setting dphase=(1<<24) will output one sample per interval. 
   Running the pwm at 9600000 / 256 samples / 256 range results
   in the waveform being output at 146.5 Hz.

   Setting dphase=(2<<24) will skip one sample per interval,
   and will double the frequency of the output to 293Hz.
   
   These functions do not return.
*/


int pause;
int skip;
int rewind;

void audio_write_i16(const int16_t waveform[], unsigned num_bytes, unsigned dphase) 
{
    unsigned phase = 0;
    int counter = 0;

    int f_counter = 0;

    int fft_n = 32;
    uint16_t out[32];

    while(1) {
        unsigned status = pwm_get_status();
        unsigned angle;
        unsigned wave;
        uint8_t pcm;
        if (rewind)
        {     
            rewind = 0;
            phase = 0;
            angle = 0;
            counter = 0;
            timer_delay_ms(500);
        }
        else if (skip)
        {
            skip = 0;
            break;
        }
        else if (!(status & PWM_FULL1) && !pause) {
            angle = phase;
            wave = waveform[angle] - INT16_MIN;
            
            pcm = wave >> 8 ;
            pwm_write( pcm ); // output to channel 0
            pwm_write( pcm ); // output to channel 1
            phase += dphase;

            // break when end of file
            if ( 2 * (dphase) * counter > num_bytes)
            {
              phase = 0;
              angle = 0;
              counter = 0;
              break;
            }
            else 
            {
              counter++;
            }
        }
        else if (pause)
        {
            timer_delay_ms(50);
        }
    }
}

/* Source: https://www.nayuki.io/res/how-to-implement-the-discrete-fourier-transform/dft.c
 * Wanted to implement a FFT during the audio; changed it to take in an array of reals
 * and output the amplitudes of the frequency domain
 */
void compute_dft_real_pair(uint16_t inreal[], uint16_t out[], int n) {
  for (int k = 0; k < n; k++) {  // For each output element
      double sumreal = 0;
      double sumimag = 0;
      for (int t = 0; t < n; t++) {  // For each input element
        double angle = 2 * M_PI * t * k / n;
        sumreal +=  inreal[t] * cos(angle);
        sumimag += -inreal[t] * sin(angle);
      }

      out[k] = (uint16_t)sqrt(pow(sumreal, 2) + pow(sumimag, 2));
  }
}
