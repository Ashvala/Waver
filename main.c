#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "waver.h"


void sin_gen(long freq, long duration, int data[duration],int samplerate){
    
    float frate= (freq*2*M_PI)/samplerate; // Frame rate -
    float frame=0; // which frame you're looking at
    float amplitude = 82000; // Amplitude
    for (int i=0; i<duration; i++){
        frame += frate; // change the frame
        data[i] = amplitude * sin(frame); // data now contains the amplitude * sin of the frame.
    }
}

int main(int argc, char *argv[]){
    if (argc == 2){
        char *flag;
        flag = "--help";
        int strcompare_res = strcmp(flag, argv[1]);
        if (strcompare_res == 0){
            system("open README.html");
        }
        
    }else{
    char *file_name = "wave.wav"; // file name
    unsigned int samplerate = SRATE; // Sample rate
    unsigned int channels = 1; // mono
    unsigned long nosamples = samplerate * 2; // two seconds of sound
    unsigned int bits_per_sample = 24; // 24 bit resolution
    int data[nosamples]; // data
    long freq = 440.0; // frequency
    wave_head_data wavedat = {file_name, samplerate, channels, nosamples, bits_per_sample}; // Wave data
    printf("If you want to learn more, execute ./%s --help\n",argv[0]);
    sin_gen(freq,nosamples,data,samplerate); // sin generation
    waver(wavedat,data); // call waver
    
    system("afplay wave.wav"); // run it, yo
    }
    return 0; // exit

}
