#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "address_map_nios2.h"
#include "fft/kiss_fft.h"

/* globals */
#define BUF_SIZE 48000    // about 10 seconds of buffer (@ 32K samples/sec)
#define BUF_THRESHOLD 96  // 75% of 128 word buffer

#define PI 3.141592653589793238462643383279502884
#define FFT_SIZE 1024 // FFT size

/* function prototypes */
void check_KEYs(int *, int *, int *);
void normalize_audio(float *, float *, int);
void hamming_window(float *, float *, int);
void fft(float *input_buffer, kiss_fft_cpx *output_buffer);

/*******************************************************************************
 * This program performs the following:
 *  1. records audio for 10 seconds when KEY[0] is pressed. LEDR[0] is lit
 *     while recording.
 *  2. plays the recorded audio when KEY[1] is pressed. LEDR[1] is lit while
 *     playing.
 ******************************************************************************/
int main(void) {
    /* Declare volatile pointers to I/O registers (volatile means that IO load
       and store instructions will be used to access these pointer locations,
       instead of regular memory loads and stores) */
    volatile int *red_LED_ptr = (int *)LED_BASE;
    volatile int *audio_ptr = (int *)AUDIO_BASE;

    /* used for audio record/playback */
    int fifospace;
    int record = 0, play = 0, buffer_index = 0;
    float left_buffer[BUF_SIZE];
    int right_buffer[BUF_SIZE];
    float normalized_buffer[BUF_SIZE];
    float windowed_buffer[BUF_SIZE];
    kiss_fft_cpx output[FFT_SIZE];

    /* read and echo audio data */
    record = 0;
    play = 0;

    while (1) {
        check_KEYs(&record, &play, &buffer_index);
        if (record) {
            *(red_LED_ptr) = 0x1;  // turn on LEDR[0]

            fifospace = *(audio_ptr + 1);  // read the audio port fifospace register
            if ((fifospace & 0x000000FF) > BUF_THRESHOLD)  // check RARC
            {
                // store data until the the audio-in FIFO is empty or the buffer is full
                while ((fifospace & 0x000000FF) && (buffer_index < BUF_SIZE)) {
                    left_buffer[buffer_index] = *(audio_ptr + 2);
                    right_buffer[buffer_index] = *(audio_ptr + 3);
                    ++buffer_index;

                    if (buffer_index == BUF_SIZE) {
                        // done recording
                        record = 0;
                        *(red_LED_ptr) = 0x0;  // turn off LEDR
                        normalize_audio(left_buffer, normalized_buffer, BUF_SIZE);
                        hamming_window(normalized_buffer, windowed_buffer, FFT_SIZE);
                        fft(windowed_buffer, output);
                        *(red_LED_ptr) = 0x8;
                        for (int i = 0; i < FFT_SIZE; i++) {
                            printf("%f\n", output[i].r);
                        }
                        printf("\n-------------\n");
                        // Reset buffer_index for the next recording
                        buffer_index = 0;
                    }
                    fifospace = *(audio_ptr + 1);  // read the audio port fifospace register
                }
            }
        }
    }
}

/****************************************************************************************
 * Subroutine to read KEYs
 ****************************************************************************************/
void check_KEYs(int *KEY0, int *KEY1, int *counter) {
    volatile int *KEY_ptr = (int *)KEY_BASE;
    volatile int *audio_ptr = (int *)AUDIO_BASE;
    int KEY_value;

    KEY_value = *(KEY_ptr);  // read the pushbutton KEY values
    while (*KEY_ptr)
        ;  // wait for pushbutton KEY release

    if (KEY_value == 0x1)  // check KEY0
    {
        // reset counter to start recording
        *counter = 0;
        // clear audio-in FIFO
        *(audio_ptr) = 0x4;
        *(audio_ptr) = 0x0;

        *KEY0 = 1;
    } else if (KEY_value == 0x2)  // check KEY1
    {
        // reset counter to start playback
        *counter = 0;
        // clear audio-out FIFO
        *(audio_ptr) = 0x8;
        *(audio_ptr) = 0x0;

        *KEY1 = 1;
    }
}

void normalize_audio(float *input_buffer, float *output_buffer, int size) {
    float max_val = 0;

    // Find the maximum absolute value
    for (int i = 0; i < size; i++) {
        float abs_val = fabs(input_buffer[i]);
        if (abs_val > max_val) {
            max_val = abs_val;
        }
    }

    // Normalize the input buffer to the range [-1, 1]
    for (int i = 0; i < size; i++) {
        output_buffer[i] = input_buffer[i] / max_val;
    }
}

void hamming_window(float *input, float *output, int size) {
    for (int i = 0; i < size; i++) {
        float alpha = 0.54f;
        float beta = 0.46f;
        float window = alpha - beta * cosf((2 * PI * i) / (size - 1));
        output[i] = input[i] * window;
    }
}

void fft(float *input_buffer, kiss_fft_cpx *output_buffer) {
    kiss_fft_cfg config;

    config = kiss_fft_alloc(FFT_SIZE, 0, NULL, NULL);

    // Convert input to kiss_fft_cpx format
    kiss_fft_cpx kiss_input_buffer[FFT_SIZE];
    for (int i = 0; i < FFT_SIZE; i++) {
        kiss_input_buffer[i].r = input_buffer[i];
        kiss_input_buffer[i].i = 0; // Assuming input is real, imaginary part is 0
    }

    // Perform FFT
    kiss_fft(config, kiss_input_buffer, output_buffer);

    // Free the FFT configuration
    kiss_fft_free(config);
}