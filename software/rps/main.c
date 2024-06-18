#include <math.h>
#include <stdlib.h>

#include "address_map_nios2.h"
#include "fft/kiss_fft.h"
#include "mfcc/libmfcc.h"
#include "altera_up_avalon_character_lcd.h";

/* globals */
#define BUF_SIZE 12000    // about 1.5 seconds of buffer (@ 8K samples/sec)
#define BUF_THRESHOLD 96  // 75% of 128 word buffer

#define FFT_SIZE 1024 // FFT size
#define FFT_SHIFT 512 // Amount of samples the FFT buffer is shifted
#define NUM_MFCC 13
#define NUM_FILTERS 12

alt_up_character_lcd_dev * char_lcd_dev;

/* function prototypes */
void check_KEYs(int *, int *, int *);
void normalize_audio(float *, float *, int);
void hamming_window(float *input, float *output, int size);
void fft(float *input_buffer, kiss_fft_cpx *output_buffer);
void calculate_mfcc(float *input_buffer, int signal_length, float *mfcc_buffer);
void clearLCD();
void writeToLCD(char* first_row, char* second_row);

/*******************************************************************************
 * This program performs the following:
 *  1. records audio for 1.5 seconds when KEY[0] is pressed.
 *  2. Normalizes the audio to a range between -1 and 1.
 *  3. Applies the Hamming window to the samples.
 ******************************************************************************/
int main(void) {
    /* Declare volatile pointers to I/O registers (volatile means that IO load
       and store instructions will be used to access these pointer locations,
       instead of regular memory loads and stores) */
    volatile int *red_LED_ptr = (int *)LED_BASE;
    volatile int *audio_ptr = (int *)AUDIO_BASE;
    int sdram_count = 0;
    int counter = 0;

    /* used for audio record and calculations */
    int fifospace;
    int record = 0, play = 0, buffer_index = 0;
    float left_buffer[BUF_SIZE];
    int right_buffer[BUF_SIZE];
    float normalized_buffer[BUF_SIZE];
    //kiss_fft_cpx output[FFT_SIZE];
    float mfcc_buffer[(BUF_SIZE / FFT_SHIFT) * NUM_MFCC];
    // open the Character LCD port
    char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/Char_LCD_16x2");
    if ( char_lcd_dev == NULL) alt_printf ("Error: could not open character LCD device\n");
    else alt_printf ("Opened character LCD device\n");
    /* Initialize the character display */
    alt_up_character_lcd_init (char_lcd_dev);
    /* Write "Welcome to" in the first row */
    alt_up_character_lcd_string(char_lcd_dev, "Press KEY0 to");
    alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "Record audio...");

    /* read and echo audio data */
    play = 0;
    int i;
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
                        //printf("Address of left_buffer: %p\n", (void*)&left_buffer);
                        clearLCD();
                        alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 0);
                        alt_up_character_lcd_string(char_lcd_dev, "Normalizing     \0");
                        alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
						alt_up_character_lcd_string(char_lcd_dev, "audio...        \0");
                        normalize_audio(left_buffer, normalized_buffer, BUF_SIZE);
                        // Calculate MFCCs
						calculate_mfcc(normalized_buffer, BUF_SIZE, mfcc_buffer);
						writeToLCD("Finished        \0", "calculations...\0");
						int num_frames = (BUF_SIZE - FFT_SIZE) / FFT_SHIFT + 1;
						for (int frame = 0; frame < num_frames; frame++) {
							printf("Frame %d:\n", frame);
							for (int m = 0; m < NUM_MFCC; m++) {
								printf("%f ", mfcc_buffer[frame * NUM_MFCC + m]);
							}
							printf("\n");
						}
                         //write the float buffer to the SDRAM

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
	float max_val = 0.0f;

	// Find the maximum absolute value
	for (int i = 0; i < size; i++) {
		float signed_val = input_buffer[i] - 32768.0f;  // Adjusting for unsigned 16-bit PCM
		float abs_val = fabs(signed_val);
		if (abs_val > max_val) {
			max_val = abs_val;
		}
	}

	// Prevent division by zero
	if (max_val == 0) {
		max_val = 1.0f;  // To avoid division by zero
	}

	// Normalize the input buffer to numbers between -1 and 1.
	for (int i = 0; i < size; i++) {
		output_buffer[i] = (input_buffer[i] - 32768.0f) / max_val;
	}
}

// Source for this function: https://www.sciencedirect.com/topics/engineering/hamming-window.
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

void calculate_mfcc(float *input_buffer, int signal_length, float *mfcc_buffer) {
    float frame[FFT_SIZE];
    float windowed_frame[FFT_SIZE];
    // Calculate how many frames can be extracted from the input signal.
    int num_frames = (signal_length - FFT_SIZE) / FFT_SHIFT + 1;

    for (int frame_num = 0; frame_num < num_frames; frame_num++) {
        // Extract FFT_SIZE samples from the start of the current frame.
        memcpy(frame, input_buffer + frame_num * FFT_SHIFT, sizeof(float) * FFT_SIZE);

        writeToLCD("Hamming         \0", "window...       \0");
        hamming_window(frame, windowed_frame, FFT_SIZE);

        writeToLCD("Performing      \0", "FFT...          \0");
        kiss_fft_cpx fft_output[FFT_SIZE];
        fft(windowed_frame, fft_output);

        writeToLCD("Magnitude       \0", "spectrum...     \0");
        // Compute the magnitude spectrum of the current frame.
        double magnitude_spectrum[FFT_SIZE];
        for (int i = 0; i < FFT_SIZE; i++) {
            magnitude_spectrum[i] = sqrt(fft_output[i].r * fft_output[i].r + fft_output[i].i * fft_output[i].i);
        }

        writeToLCD("Calculating     \0", "MFCCs...        \0");
        // Calculate MFCCs for the current frame.
        for (int m = 0; m < NUM_MFCC; m++) {
            mfcc_buffer[frame_num * NUM_MFCC + m] = GetCoefficient(magnitude_spectrum, 8192, NUM_FILTERS, FFT_SIZE, m);
        }
    }
}

void clearLCD() {
	for (int i = 0; i < 16; i++) {
		alt_up_character_lcd_erase_pos(char_lcd_dev, i, 0);
		alt_up_character_lcd_erase_pos(char_lcd_dev, i, 1);
	}
}

void writeToLCD(char* first_row, char* second_row) {
	clearLCD();
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 0);
	alt_up_character_lcd_string(char_lcd_dev, first_row);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, second_row);
}
