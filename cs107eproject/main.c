#include "timer.h"
#include "gpio.h"
#include "pwm.h"
#include "tone.h"
#include "pitch.h"
#include "fs.h"
#include "strings.h"
#include "gpioextra.h"
#include "malloc.h"
#include "printf.h"
#include "audio.h"
#include "assert.h"
#include "audio_play.h"
#include "interrupts.h"

#include <math.h>
#include "edmtest.h"
#include "pickitup.h"
#include "stay.h"
#include "middle.h"
#include "closer.h"
#include "howlong.h"
#include "sad.h"
#include "allthestars.h"


int format_header(const int16_t mywave[], int length, char* fmt);

// notes in the melody:
// note durations: 4 = quarter note, 8 = eighth note, etc.:


// taken from https://gist.github.com/Jon-Schneider/8b7c53d27a7a13346a643dac9c19d34f
typedef struct wav_header {
    // RIFF Header
    char riff_header[4]; // Contains "RIFF"
    unsigned wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
    char wave_header[4]; // Contains "WAVE"
    
    // Format Header
    char fmt_header[4]; // Contains "fmt " (includes trailing space)
    int fmt_chunk_size; // Should be 16 for PCM
    short audio_format; // Should be 1 for PCM. 3 for IEEE Float
    short num_channels;
    int sample_rate;
    int byte_rate; // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    short sample_alignment; // num_channels * Bytes Per Sample
    short bit_depth; // Number of bits per sample
    
    // List Header
    char list_header[34];

    // Data Header
    char data_header[4]; // Contains "data"
    int data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size

    // uint8_t bytes[]; // Remainder of wave file is bytes
} wav_header;

int pause;
int skip;
int rewind;

void main ( void )
{
    pwm_init();
	audio_play_init();
	interrupts_global_enable();

    wav_header* song_info = malloc(sizeof(wav_header));
    

    while (1)
    {

        // read the WAV header in and then play the music
        format_header(pickitup, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(pickitup + sizeof(wav_header), song_info->wav_size, 2);
        timer_delay(2);

        format_header(edmtest, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(edmtest + sizeof(wav_header), song_info->wav_size, 2);
        timer_delay(2);

        format_header(stay, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(stay + sizeof(wav_header), song_info->wav_size, 1);
        timer_delay(2);

        format_header(sad, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(sad + sizeof(wav_header), song_info->wav_size, 1);
        timer_delay(2);

        format_header(allthestars, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(allthestars + sizeof(wav_header), song_info->wav_size, 1);
        timer_delay(2);

        format_header(middle, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(middle + sizeof(wav_header), song_info->wav_size, 1);
        timer_delay(2);

        format_header(howlong, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(howlong + sizeof(wav_header), song_info->wav_size, 1);
        timer_delay(2);

        format_header(closer, sizeof(wav_header) / 2, (char*)song_info);
        audio_write_i16(closer + sizeof(wav_header), song_info->wav_size, 1);
        timer_delay(2);
    }
    




}

// Reads the WAV file header information into an array
int format_header(const int16_t mywave[], int length, char* fmt)
{
	for (int i = 0; i < length; i++)
	{
		fmt[2 * i] = mywave[i] & 0xff;
		fmt[2 * i + 1] = mywave[i] >> 8;
	}

	char* test = malloc(5);
	for (int j = 0; j < 4; j++)
	{
		test[j] = fmt[j];
	}
	test[4] = '\0';
	return 0;
}
