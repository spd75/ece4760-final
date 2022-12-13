#include "global.h"
#include "sound.h"
#include "vga_graphics.h"
// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
// Include Pico libraries
#include "pico/stdlib.h"
// Include hardware libraries
#include "hardware/pio.h"
#include "hardware/spi.h"
// Include protothreads

fix15 sin_table[sine_table_size]; 

uint16_t DAC_data;                      // Data that is output to DAC
int DAC_output;                         // DAC output
fix15 max_amplitude = int2fix15(1);     // Max amplitude for sound
fix15 attack_inc;                       // Attack incrementor for attack period            
fix15 decay_inc;                        // Decay incrementor for decay period

unsigned int accumulators[5] = {0};     // Accumulators for each column
unsigned int incrementors[5] = {0};     // Incrementors for each column
int amplitude[5] = {0};                 // Amplitude for each column
int counter[5] = {0};                   // Counter for each column

// Generate sound by setting incrementor to corresponding value based on frequency
void generateSoundPlay(float frequency) {
    int i = 0;
    while (incrementors[i] != 0) {
        i += 1;
    }
 
    if (i < 5) {
        incrementors[i] = frequency*two32/Fs;
    }
}

// Generate synth notes
void soundGeneration() {
    int numUsed = 0;

    // Loop over all columns to see if any of them have a note to be played
    for (int i = 0; i < 5; i++) {
        // If corresponding incrementor is 0 then this mean no sound needs to be played for this note, so skip over
        if (incrementors[i] == 0) {
            continue;
        }
        numUsed += 1;                                       // Increment soundUsed to switch channel if more than one note is being played
        accumulators[i] += incrementors[i];                 // Increment accumulator by the appropriate incrementor
        DAC_output = fix2int15(multfix15(amplitude[i],
            sin_table[accumulators[i]>>24])) + 2048;

        // Ramp up amplitude
        if (counter[i] < ATTACK_TIME) {
            amplitude[i] = (amplitude[i] + attack_inc);
        }
        // Ramp down amplitude
        else if (counter[i] > NOTE_DURATION - DECAY_TIME) {
            amplitude[i] = (amplitude[i] - decay_inc);
        }

        // Mask with DAC control bits
        if (numUsed % 2 == 0) {
            DAC_data = (DAC_config_chan_A | (DAC_output & 0xffff));
        } else {
            DAC_data = (DAC_config_chan_B | (DAC_output & 0xffff));
        }

        // SPI write (no spinlock b/c of SPI buffer)
        spi_write16_blocking(spi0, &DAC_data, 1);

        // Increment the counter
        counter[i] += 1 ;

        // Resets accumulators, incremetors, amplitude, and counter
        if (counter[i] >= NOTE_DURATION) {
            accumulators[i] = 0;
            incrementors[i] = 0;
            amplitude[i] = 0;
            counter[i] = 0;
        }
    }
}

void initializeForSoundProduction() {
    // Initialize attack and decay incrementors
    attack_inc = divfix(max_amplitude, int2fix15(ATTACK_TIME));
    decay_inc =  divfix(max_amplitude, int2fix15(DECAY_TIME));

    // Create sine table for synth -- equation was custom designed by us to produce appropriate sound
    for (int ii = 0; ii < sine_table_size; ii++){
        float amp = 1000;
        float a = 0.15*amp*sin(1.571+(float)12.566*ii/(float)sine_table_size);
        float b = -0.3*amp*sin(((float)18.849*ii/(float)sine_table_size)-0.523);
        float c = 0.5*amp*sin((float)6.283*ii/(float)sine_table_size);
        float d = 0.45*amp*sin(0.785+(float)6.283*ii/(float)sine_table_size);
        float e = 0.7*amp*sin((float)6.283*ii/(float)sine_table_size);

        fix15 val = float2fix15(a + b + c + d + e);
        sin_table[ii] = val;
    }
}

