#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

void audio_init(void);

void audio_write_i16(const int16_t waveform[], unsigned num_bytes, unsigned dphase);

#endif
