#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>

#include "address_map_nios2.h"
#include "kiss_fft.h"


/* globals */
#define BUF_SIZE 48000    // about 10 seconds of buffer (@ 32K samples/sec)
#define BUF_THRESHOLD 96  // 75% of 128 word buffer

#define PI 3.141592653589793238462643383279502884
#define FFT_SIZE 1024 // FFT size

/* function prototypes */
void check_KEYs(int *, int *, int *);
void normalize_audio(float *, float *, int);
void denormalize_audio(float *, float *, int);
void fft_example(float *input, kiss_fft_cpx *output);

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
  volatile int *red_LED_ptr = (int *)LED_BASE;
  volatile int *audio_ptr = (int *)AUDIO_BASE;

  /* used for audio record/playback */
  int fifospace;
  int record = 0, play = 0, buffer_index = 0;
  float left_buffer[BUF_SIZE];
  int right_buffer[BUF_SIZE];
  float normalized_buffer[BUF_SIZE];
  float denormalized_buffer[BUF_SIZE];
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
            *(red_LED_ptr) = 0x4;
            normalize_audio(left_buffer, normalized_buffer, BUF_SIZE);
            *(red_LED_ptr) = 0x8;
            // denormalize_audio(left_buffer, normalized_buffer, BUF_SIZE);
            fft_example(normalized_buffer, output);
            *(red_LED_ptr) = 0x4;
            for (int i = 0; i < FFT_SIZE; i++) {
              printf("%f\n", output[i]);
            }
            printf("\n-------------\n");
          }
          fifospace =
              *(audio_ptr + 1);  // read the audio port fifospace register
        }
      }
    } else if (play) {
      buffer_index = 0; // reset buffer index for playback
      denormalize_audio(normalized_buffer, left_buffer, BUF_SIZE);
      printf("denormalized samples:\n");
      for (int i = 48000; i < 54000; i++) {
    	  printf("%f\n", left_buffer[i]);
      }
      *(red_LED_ptr) = 0x2;          // turn on LEDR_1
      fifospace = *(audio_ptr + 1);  // read the audio port fifospace register
      if ((fifospace & 0x00FF0000) > BUF_THRESHOLD)  // check WSRC
      {
        // output data until the buffer is empty or the audio-out FIFO is full
        /*while ((fifospace & 0x00FF0000) && (buffer_index < BUF_SIZE)) {
          *(audio_ptr + 2) = left_buffer[buffer_index];
          *(audio_ptr + 3) = left_buffer[buffer_index];
          ++buffer_index;

          if (buffer_index == BUF_SIZE) {
            // done playback
            play = 0;
            *(red_LED_ptr) = 0x0;  // turn off LEDR
          }
          fifospace =
              *(audio_ptr + 1);  // read the audio port fifospace register
        }*/
    	  while (buffer_index < BUF_SIZE) {
			*(audio_ptr + 2) = left_buffer[buffer_index];
			*(audio_ptr + 3) = left_buffer[buffer_index];
			++buffer_index;

			if (buffer_index == BUF_SIZE) {
			  // done playback
			  play = 0;
			  *(red_LED_ptr) = 0x0;  // turn off LEDR
			}
			fifospace =
				*(audio_ptr + 1);  // read the audio port fifospace register
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
  }
  else if (KEY_value == 0x2)  // check KEY1
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
    int max_val = 0;

    // Convert unsigned values to signed values and find the maximum absolute value
    for (int i = 0; i < size; i++) {
        int signed_val = input_buffer[i] - 32768;
        int abs_val = abs(signed_val);
        if (abs_val > max_val) {
            max_val = abs_val;
        }
    }

    // Normalize the input buffer to the range [-1, 1]
    for (int i = 0; i < size; i++) {
        output_buffer[i] = (float)(input_buffer[i] - 32768) / max_val;
    }
}

void denormalize_audio(float *input_buffer, float *output_buffer, int size) {
    int max_val = 32767;  // Maximum value for 16-bit audio

    // Denormalize the input buffer back to the range of the original audio
    for (int i = 0; i < size; i++) {
        output_buffer[i] = input_buffer[i] * max_val + 32768;
    }
}

void pre_emphasis(float *signal, float *pre_emphasized, int size, float alpha) {
    pre_emphasized[0] = signal[0];
    for (int i = 1; i < size; i++) {
        pre_emphasized[i] = signal[i] - alpha * signal[i - 1];
    }
}

void frame_blocking(float *signal, float **frames, int signal_size, int frame_size, int frame_stride) {
    int num_frames = 1 + (signal_size - frame_size) / frame_stride;
    for (int i = 0; i < num_frames; i++) {
        for (int j = 0; j < frame_size; j++) {
            frames[i][j] = signal[i * frame_stride + j];
        }
    }
}

void hamming_window(float *frame, int frame_size) {
    for (int i = 0; i < frame_size; i++) {
        frame[i] *= 0.54 - 0.46 * cos(2 * PI * i / (frame_size - 1));
    }
}


void fft_example(float *input, kiss_fft_cpx *output) {

    kiss_fft_cfg cfg;

    cfg = kiss_fft_alloc(FFT_SIZE, 0, 0, 0);


    kiss_fft(cfg, input, output);


    kiss_fft_free(cfg);

}

void mel_filter_bank(float *power_spectrum, float *mel_energies, int num_filters, int fft_size, int sample_rate) {
    int low_freq_mel = 0;
    int high_freq_mel = (2595 * log10(1 + (sample_rate / 2) / 700.0));
    int mel_points[num_filters + 2];

    for (int i = 0; i < num_filters + 2; i++) {
        mel_points[i] = (fft_size + 1) * (700 * (pow(10, (low_freq_mel + i * (high_freq_mel - low_freq_mel) / (num_filters + 1)) / 2595.0) - 1)) / sample_rate;
    }

    for (int i = 0; i < num_filters; i++) {
        for (int j = mel_points[i]; j < mel_points[i + 1]; j++) {
            mel_energies[i] += (j - mel_points[i]) / (mel_points[i + 1] - mel_points[i]) * power_spectrum[j];
        }
        for (int j = mel_points[i + 1]; j < mel_points[i + 2]; j++) {
            mel_energies[i] += (mel_points[i + 2] - j) / (mel_points[i + 2] - mel_points[i + 1]) * power_spectrum[j];
        }
        mel_energies[i] = log(mel_energies[i]);
    }
}

void dct(float *mel_energies, float *mfcc, int num_filters, int num_coefficients) {
    for (int i = 0; i < num_coefficients; i++) {
        mfcc[i] = 0;
        for (int j = 0; j < num_filters; j++) {
            mfcc[i] += mel_energies[j] * cos(PI * i * (2 * j + 1) / (2 * num_filters));
        }
    }
}

void calculate_mfcc(float *signal, int signal_size, int sample_rate, int frame_size, int frame_stride, int num_filters, int num_coefficients, float *mfcc_result) {
    int num_frames = 1 + (signal_size - frame_size) / frame_stride;
    float **frames = (float **)malloc(num_frames * sizeof(float *));
    for (int i = 0; i < num_frames; i++) {
        frames[i] = (float *)malloc(frame_size * sizeof(float));
    }

    // Step 1: Pre-emphasis
    float pre_emphasized[signal_size];
    pre_emphasis(signal, pre_emphasized, signal_size, 0.97);

    // Step 2: Frame Blocking
    frame_blocking(pre_emphasized, frames, signal_size, frame_size, frame_stride);

    // Step 3: Windowing and FFT
    float power_spectrum[frame_size / 2 + 1];
    float mel_energies[num_filters];
    float mfcc[num_coefficients];
    for (int i = 0; i < num_frames; i++) {
        hamming_window(frames[i], frame_size);
        //fft_and_power_spectrum(frames[i], power_spectrum, frame_size);
        mel_filter_bank(power_spectrum, mel_energies, num_filters, frame_size, sample_rate);
        dct(mel_energies, mfcc, num_filters, num_coefficients);

        for (int j = 0; j < num_coefficients; j++) {
            mfcc_result[i * num_coefficients + j] = mfcc[j];
        }
    }

    // Free memory
    for (int i = 0; i < num_frames; i++) {
        free(frames[i]);
    }
    free(frames);
}
