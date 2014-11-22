
#include <iostream>
#include <soundtouch/SoundTouch.h>
#include "eus_wav_util.cpp"

using namespace soundtouch;

static soundtouch::SoundTouch soundTouch;
static soundtouch::SoundTouch* pSoundTouch = &soundTouch;

// SAMPLETYPE* short_sound_array_buf;
// int short_sound_array_buf_size=-1;

// void checkSizeOfBuffer(int size){
//   if ( size <= short_sound_array_buf_size ){
//     free(short_sound_array_buf);
//     short_sound_array_buf = (SAMPLETYPE *)malloc( sizeof(SAMPLETYPE) * size );
//     short_sound_array_buf_size = size ;
//   }
// }

extern "C" {
  int setParamSoundTouch(int samplerate, int channel, float tempo, float pitch, float rate){
    pSoundTouch->setSampleRate(samplerate);
    pSoundTouch->setChannels(channel);
    pSoundTouch->setTempoChange(tempo);
    pSoundTouch->setPitchSemiTones(pitch);
    pSoundTouch->setRateChange(rate);
    return 1;
  }
}

extern "C" {
  int putSampleSoundTouch(int* array, int size, int channel){
    int i;
    checkSizeOfBuffer(size);
    for ( i=0; i<size ; i++ ){
      short_sound_array_buf[i] = (SAMPLETYPE)array[i] ;
    }
    pSoundTouch->putSamples(short_sound_array_buf, size/channel);
    return (size/channel);
  }
}

extern "C" {
  int receiveSampleSoundTouch(int* array, int size, int channel){
    int i ,ret;
    checkSizeOfBuffer(size);
    ret = pSoundTouch->receiveSamples(short_sound_array_buf, size/channel);
    for ( i=0; i<size ; i++ ){
      array[i] = (int)short_sound_array_buf[i];
    }
    return ret ;
  }
}

extern "C" {
  int flushSoundTouch(){
    pSoundTouch->flush();
    return 1;
  }
}

extern "C" {
  int initSoundTouch(){
    setParamSoundTouch(8000,1,1.0f,1.0f,1.0f);
    flushSoundTouch();
    return 0;
  }
}

// wav utils

extern "C"{
  void closeInWavFile(){ _closeInWavFile(); }
}

extern "C"{
  void openInWavFile(char *file_name, int* buf) {
    _openInWavFile(file_name,buf);
  }
}

extern "C"{
  void closeOutWavFile(){ _closeOutWavFile(); }
}

extern "C"{
  void openOutWavFile(char *file_name, int samplerate, int bits, int channels) {
    _openOutWavFile(file_name,samplerate,bits,channels);
  }
}

extern "C"{
  int readWavFile(int* buffer, int size){
    return _readWavFile(inFile, buffer, size);
  }
}

extern "C"{
  void writeWavFile(int* buffer, int size){
    return _writeWavFile(outFile, buffer, size);
  }
}
