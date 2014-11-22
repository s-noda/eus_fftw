
#include <soundtouch/SoundTouch.h>
#include <soundtouch/BPMDetect.h>
#include "WavFile.h"
#include "WavFile.cpp"

using namespace soundtouch;
using namespace std;

WavInFile *inFile;
WavOutFile *outFile;
SAMPLETYPE* short_sound_array_buf;
int short_sound_array_buf_size=-1;

void checkSizeOfBuffer(int size){
  if ( size <= short_sound_array_buf_size ){
    free(short_sound_array_buf);
    short_sound_array_buf = (SAMPLETYPE *)malloc( sizeof(SAMPLETYPE) * size );
    short_sound_array_buf_size = size ;
  }
}

void _closeInWavFile(){
  if ( inFile != NULL ) {
    delete inFile;
  }
}


void _openInWavFile(char *file_name, int* ret) {
  _closeInWavFile();
  inFile = new WavInFile(file_name);
  int bits = (int)(inFile)->getNumBits();
  int samplerate = (int)(inFile)->getSampleRate();
  int channels = (int)(inFile)->getNumChannels();
  // *outFile = new WavOutFile(params->outFileName, samplerate, bits, channels);
  ret[0]=bits;
  ret[1]=samplerate;
  ret[2]=channels;
}

void _closeOutWavFile(){
  if ( outFile != NULL ) {
    delete outFile;
  }
}

void _openOutWavFile(char *file_name, int samplerate, int bits, int channels) {
  _closeOutWavFile();
  outFile = new WavOutFile(file_name, samplerate, bits, channels);
}

int _readWavFile(WavInFile *inFile, int* buffer, int size){
  int num = -1;
  int i;
  checkSizeOfBuffer(size);
  if (inFile->eof() == 0){
    num = inFile->read(short_sound_array_buf, size);
  }
  for ( i=0 ; i<num ; i++ ){
    buffer[i] = (int)short_sound_array_buf[i];
  }
  return num;
}

void _writeWavFile(WavOutFile *outFile, int* buffer, int size){
  int i;
  checkSizeOfBuffer(size);
  for ( i=0 ; i<size ; i++ ){
    short_sound_array_buf[i] = (SAMPLETYPE)buffer[i];
  }
  outFile->write(short_sound_array_buf, size);
}

