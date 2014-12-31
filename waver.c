/*
 The purpose of this is to create a WAV file generator, similar to StupidSimpleSynth.
 
 The WAV spec can be found here: https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
 
 Quick one about WAV files:
 
 The header chunk contains A RIFF chunk. RIFF is "resource interchange file format", which essentially tells whatever decodes a WAV file that it's a WAV file...
 
 The format chunk contains the essentials, Number of Channels, Sample Rate, Byte Rate, Bits per Sample and so on.
 
 The data chunk contains the... well, data.
 
 Most of the code was inspired by Kevin Karplus' article on writing a wave file with C. It can be found here:
 http://gasstationwithoutpumps.wordpress.com/2011/10/08/making-wav-files-from-c-programs/
 */

#include <stdio.h>
#include <math.h>

#include "waver.h"

// Borrowed this function from Karplus. It seems like the only safe way so far to write Little Endian encoded values to a file.

void write_little_endian(unsigned int word, unsigned int num_bytes, FILE *wav_file)
{
    int buf;
    while(num_bytes>0)
    {   buf = word & 0xff; // represent least significant bit
        fwrite(&buf, 1,1, wav_file);
        num_bytes--; // go back
        word >>= 8;
    }
}

void waver(wave_head_data wavedat,int *data){
    printf("File name is:%s\n", wavedat.file_name); // print the file name into command line or console(if you use XCode)!
    FILE* wav_file; // define file
    int bytes = wavedat.bits/8;

    unsigned int byte_rate; // byte rate is samplerate*channels*bytespersample
    unsigned int block_align; // Block align is channels * (bitspersample/8)
    unsigned long sc2s = wavedat.nosamples * wavedat.channels * bytes; // Subchunk2 Size is samples * channels * (bitspersample/8)
    unsigned int chunksize =  36 + (byte_rate)* ((int)wavedat.nosamples)*(wavedat.channels); // chunksize
    byte_rate = wavedat.samplerate*wavedat.channels*bytes; //calculate  byte_rate
    block_align = wavedat.channels* bytes; // calculate block align
    wav_file = fopen(wavedat.file_name, "w"); // open wave file.
    // RIFF Chunk
    fwrite("RIFF", 1, 4, wav_file); // Declare that it's a RIFF file
    write_little_endian(chunksize, 4, wav_file); // Write chunk size - 4 bytes
    fwrite("WAVE", 1, 4, wav_file); // Write WAVE, declaring that it's actually a WAVE file now!
    // Format Chunk
    fwrite("fmt ", 1, 4, wav_file); // Write "FMT"
    write_little_endian(16, 4, wav_file); // Subchunk 1 size, it's 16 if you want to keep it in PCM
    write_little_endian(1, 2, wav_file); // PCM = 1 | Audio format tag
    write_little_endian(1,2,wav_file); // Number of channels we want
    write_little_endian(wavedat.samplerate,4,wav_file); // Sample Rate
    write_little_endian(byte_rate,4,wav_file); // Byte Rate
    write_little_endian(block_align,2,wav_file); // block align
    write_little_endian(wavedat.bits,2,wav_file); // bits per sample
    // Data Chunk
    fwrite("data",1,4,wav_file); // write Data
    write_little_endian((unsigned int)sc2s, 4, wav_file); // write SubChunk2 size
    for(int i = 0; i < wavedat.nosamples; i++){
        write_little_endian((unsigned int)data[i],bytes, wav_file); // write data
    }
    fclose(wav_file);
}
