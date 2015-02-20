#ifndef WAVER_H_
#define WAVER_H_
  
#define SRATE 44100 // Sample rate

typedef struct{
    char *file_name; // file name
    unsigned int samplerate; // sample rate
    unsigned int channels; // channels | 1 or 2, yo
    unsigned long nosamples; // size
    unsigned int bits; // bit resolution. 
    
}wave_head_data; // define a structure that contains most of the header data 

void waver(wave_head_data,int *data); // prototype the waver function

#endif
