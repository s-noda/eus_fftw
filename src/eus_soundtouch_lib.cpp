
#include <iostream>
#include <soundtouch/SoundTouch.h>

using namespace soundtouch;

soundtouch::SoundTouch soundTouch;
soundtouch::SoundTouch* pSoundTouch = &soundTouch;

SAMPLETYPE* short_sound_array_buf;
int short_sound_array_buf_size=-1;

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
void checkSizeOfBuffer(int size){
  if ( size != short_sound_array_buf_size ){
    free(short_sound_array_buf);
    short_sound_array_buf = (SAMPLETYPE *)malloc( sizeof(SAMPLETYPE) * size );
    short_sound_array_buf_size = size ;
  }
}
}

extern "C" {
int putSampleSoundTouch(int* array, int size, int channel){
  int i;
  checkSizeOfBuffer(size);
  for ( i=0; i<size ; i++ ){
    short_sound_array_buf[i] = (short)array[i] ;
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

