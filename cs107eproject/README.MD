# Retrofitted LED Speaker System
Alex Lee and Tiger Sun

![alt tag](https://snag.gy/K3fnLP.jpg "Our box!")

## Description
This project was for the final project of CS107e (Computer Systems from the Ground Up) class at Stanford. We worked with a bare-metal Raspberry Pi and wrote the libraries for the RPi as part of the class. We coded in C.

## Goal
Our goal was to retrofit an old, vintage speaker system, and attach speakers and LED's to it. We would attempt to play audio from the SD card to the speakers, and we wanted to do a sort of audio visualization algorithm to link the audio and LEDs together.

## Description and Process
We had two main components for this project: audio and LED strips. For audio, we used computer speakers and for LEDS, we used  a WS2812B LED strip. For our box, we went thrift shopping at Goodwill and found a great looking antique boombox.

We were able to download audio in the form of WAV files from the Internet, such as through YouTube, and interpret it into audio, and display a pretty show of lighted LED strips. There were several components and process that we had to be aware of. We had to be able to manipulate memory to read the WAV header file, and understand the fundamental ideas behind PWM and audio, such as amplitude, frequency, and endian-ness. We were originally planning on using the fs.h file system library to read our audio, but discovered there were some bugs with values past 0x8000. In order to work around this, Mark advised us to write our own script to put everything into a header file containing a C-style array. This worked, and after making sure our endian values were correct, we could play audio! LEDs also presented a different in challenge, in that timing was essential. We wrote inline assembly nop commands to take up the necessary amount of time to differentiate between highs and lows, and in doing so, we were finally able to control which colors we wanted on and how many LEDs we wanted to light. Finally, we wanted to combine both these aspects of audio and light together in the form of a Fast Fourier Transform, where we would base which colors/numbers of pixels depending on the frequency domain of our FFT on our array values. However, we ran into issues when we tried to incorporate lights with audio, as it would cause a slight clicking sound during the audio. We decided to showcase these two parts separately during our demo.

### AUDIO:
https://gist.github.com/Jon-Schneider/8b7c53d27a7a13346a643dac9c19d34f We used this header to help read WAV file information. We modified it by adding an additional "LIST" format section that was present on the audio that we had downloaded.

### LEDS:
https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/ we used the code given from this source (which was for Arduino) and adapted it to the Raspberry Pi.

### FFT:
https://www.nayuki.io/res/how-to-implement-the-discrete-fourier-transform/dft.c we used this code to try our Fast Fourier Transform. It was originally adapted for complex numbers, but we input real values and output the amplitudes of complex values (which would be real) so it was essentially a real to real conversion. Though, we didn't ultimately use the FFT, we thought it was a neat concept to wrap our minds around.

### INTERRUPTS:
We planned on demoing interrupts as well with buttons to pause, skip, and rewind the song, but mysteriously, a few hours before demo, the buttons stopped working, and we weren't able to debug this in time.

## TASKS

### Tiger
I worked mostly on the audio and interrupt portion, and a little bit of debugging on LEDs and FFT. I first parsed through the file system code, which was buggy unfortunately. I wrote a hexdump code for the file system and compared it to the actual hexdump and found that it differed after address 0x8000, where it would then repeat values from ~0x50 - ~0x8000 over and over again to 0x10000 and so on.

To circumvent this, I wrote a script to create a C style array of int16_t's that would end up being our audio signal that we would read. For this part, I had to look at the endian things to make sure that bytes were being converted over properly. I modified the given audio.c files in order to play the entire song. We also had to modify the dphase part of the audio to suit ourselves. The most difficult part about idea was probably understanding how the PWM and FIFO worked with each other with the PWM_CLOCK for timing, and I spent a lot of time parsing through the given audio code.

To complement this I worked on interrupts as well, that worked well initially. I had a button that paused, one that skipped, and one that rewinded, but unfortunately, a bug knocked these out at the last moment. I helped debug on LED's by using extensive for loop testing with baselines to determine the number of nanoseconds taken by a single nop operator, which Alex used to time the strip and send the correct bits over. I also attempted to write the script for the FFT, but we didn't end up putting it into use. I think I learned a lot about the Fourier transform through this research though, especially what it actually does physically with the frequency domain and roots of unity.

### Alex
I initially tried to work on the audio files with Tiger, but when the LEDs came in the mail, it was more efficient to work on the LEDs instead of working with him on the audio. I worked on getting the LEDs to work and unfortunately getting the timing to work for sending bits took extremely long. But after two straight days of playing with the asm loops, Tiger and I finally figured out how long one asm not takes to do and I used that information to try to fine tune the timing. And finally, we managed to get the timing working to get the right colors on the led strips. I wrote up the code that we could have used if we managed to get the FFT code in time but unfortunately we couldn't get all of it working together in time. 

The frame function at the bottom of neopixels.c file basically works so that it can be called in the audio.c with the wave variable, which is the amplitude, so that it can display x number of pixels depending on the amplitude.

I implemented several different showColor functions that can set the LED strips depending on if you want all of the strip lit or a certain number of pixels. Also, you can call showGivenColor functions and give it a color of unsigned int type and it'll display the same thing. When working with more than one LED strips, I have it currently set for it to be 10 pixels per a strip. So you would need to call the showColor functions x number of times for x number of strips and then call show(). 
