#include "address_map_nios2.h"
#include <stdlib.h>
#include <stdio.h>

/* globals */
#define BUF_SIZE 96000  // about 10 seconds of buffer (@ 32K samples/sec)
#define BUF_THRESHOLD 96 // 75% of 128 word buffer

#define PI 3.141592653589793238462643383279502884

/* function prototypes */
void check_KEYs(int *, int *, int *);
void normalize_audio(short int *, float *, int);
void denormalize_audio(short int *, float *, int);

/*******************************************************************************
 * This program performs the following:
 * 	1. records audio for 10 seconds when KEY[0] is pressed. LEDR[0] is lit
 *	   while recording.
 * 	2. plays the recorded audio when KEY[1] is pressed. LEDR[1] is lit while
 *	   playing.
 ******************************************************************************/
int main(void) {
    /* Declare volatile pointers to I/O registers (volatile means that IO load
       and store instructions will be used to access these pointer locations,
       instead of regular memory loads and stores) */
    volatile int * red_LED_ptr = (int *)LED_BASE;
    volatile int * audio_ptr   = (int *)AUDIO_BASE;

    /* used for audio record/playback */
    int fifospace;
    int record = 0, play = 0, buffer_index = 0;
    float left_buffer[BUF_SIZE];
    int right_buffer[BUF_SIZE];
    float normalized_buffer[BUF_SIZE];

    /* read and echo audio data */
    record = 0;
    play   = 0;

    while (1) {
        check_KEYs(&record, &play, &buffer_index);
        if (record) {
            *(red_LED_ptr) = 0x1; // turn on LEDR[0]

            fifospace = *(audio_ptr + 1); // read the audio port fifospace register
            if ((fifospace & 0x000000FF) > BUF_THRESHOLD) // check RARC
            {
                // store data until the the audio-in FIFO is empty or the buffer is full
                while ((fifospace & 0x000000FF) && (buffer_index < BUF_SIZE)) {
                    left_buffer[buffer_index]  = *(audio_ptr + 2);
                    //printf("%d\n", *(audio_ptr + 2));
                    //right_buffer[buffer_index] = *(audio_ptr + 3);
                    right_buffer[buffer_index] = *(audio_ptr + 3);
                    ++buffer_index;

                    if (buffer_index == BUF_SIZE) {
                        // done recording
                        record = 0;
                        *(red_LED_ptr) = 0x0; // turn off LEDR
                        *(red_LED_ptr) = 0x4;
                        //normalize_audio(left_buffer, normalized_buffer, BUF_SIZE);
                        //denormalize_audio(left_buffer, normalized_buffer, BUF_SIZE);
                        *(red_LED_ptr) = 0x0;
                        for (int i = 48000; i < 54000; i++) {
                            printf("%f\n", left_buffer[i]);
                        }
                        printf("\n-------------\n");
                    }
                    fifospace = *(audio_ptr + 1); // read the audio port fifospace register
                }
            }
        } else if (play) {
            //buffer_index = 0; // reset buffer index for playback
            //denormalize_audio(normalized_buffer, left_buffer, BUF_SIZE);
            *(red_LED_ptr) = 0x2; // turn on LEDR_1
            fifospace = *(audio_ptr + 1); // read the audio port fifospace register
            if ((fifospace & 0x00FF0000) > BUF_THRESHOLD) // check WSRC
            {
                // output data until the buffer is empty or the audio-out FIFO is full
                while ((fifospace & 0x00FF0000) && (buffer_index < BUF_SIZE)) {
                    *(audio_ptr + 2) = left_buffer[buffer_index];
                    *(audio_ptr + 3) = left_buffer[buffer_index];
                    ++buffer_index;

                    if (buffer_index == BUF_SIZE) {
                        // done playback
                        play = 0;
                        *(red_LED_ptr) = 0x0; // turn off LEDR
                    }
                    fifospace = *(audio_ptr + 1); // read the audio port fifospace register
                }
            }
        }
    }
}

/****************************************************************************************
 * Subroutine to read KEYs
****************************************************************************************/
void check_KEYs(int * KEY0, int * KEY1, int * counter) {
    volatile int * KEY_ptr   = (int *)KEY_BASE;
    volatile int * audio_ptr = (int *)AUDIO_BASE;
    int KEY_value;

    KEY_value = *(KEY_ptr); // read the pushbutton KEY values
    while (*KEY_ptr); // wait for pushbutton KEY release

    if (KEY_value == 0x1) // check KEY0
    {
        // reset counter to start recording
        *counter = 0;
        // clear audio-in FIFO
        *(audio_ptr) = 0x4;
        *(audio_ptr) = 0x0;

        *KEY0 = 1;
    }
    else if (KEY_value == 0x2) // check KEY1
    {
        // reset counter to start playback
        *counter = 0;
        // clear audio-out FIFO
        *(audio_ptr) = 0x8;
        *(audio_ptr) = 0x0;

        *KEY1 = 1;
    }
}

void normalize_audio(short int *input_buffer, float *output_buffer, int size) {
    int max_val = 0;
    // Find the maximum absolute value in the input buffer
    for (int i = 0; i < size; i++) {
        int abs_val = abs(input_buffer[i]);
        if (abs_val > max_val) {
            max_val = abs_val;
        }
    }
    // Normalize the input buffer to the range [-1, 1]
    for (int i = 0; i < size; i++) {
        output_buffer[i] = (float)input_buffer[i] / max_val;
    }
}

void denormalize_audio(short int *input_buffer, float *output_buffer, int size) {
    int max_val = 32767; // Assuming 16-bit audio
    // Denormalize the input buffer back to the range of the original audio
    for (int i = 0; i < size; i++) {
        output_buffer[i] = (float)input_buffer[i] * max_val;
    }
}
