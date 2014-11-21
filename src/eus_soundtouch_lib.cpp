
#include <iostream>
#include <soundtouch/SoundTouch.h>

using namespace soundtouch;

soundtouch::SoundTouch soundTouch;
soundtouch::SoundTouch* pSoundTouch = &soundTouch;

short* short_sound_array_buf;
int short_sound_array_buf_size=-1;

int setParamSoundTouch(int samplerate, int channel, float tempo, float pitch, float rate){
  pSoundTouch->setSampleRate(samplerate);
  pSoundTouch->setChannels(channel);
  pSoundTouch->setTempoChange(tempo);
  pSoundTouch->setPitchSemiTones(pitch);
  pSoundTouch->setRateChange(rate);
  return 1;
}

int putSampleSoundTouch(int* array, int size, int channel){
  int i;
  if ( size != short_sound_array_buf_size ){
    free(short_sound_array_buf);
    short_sound_array_buf = (short *)malloc( sizeof(short) * size );
    short_sound_array_buf_size = size ;
  }
  for ( i=0; i<size ; i++ ){
    short_sound_array_buf[i] = (short)array[i] ;
  }
  return pSoundTouch->putSamples(short_sound_array_buf, size/channel);
}

int receiveSampleSoundTouch(int* array, int size, int channel){
  int i ,ret;
  if ( size != short_sound_array_buf_size ){
    free(short_sound_array_buf);
    short_sound_array_buf = (short *)malloc( sizeof(short) * size );
    short_sound_array_buf_size = size ;
  }
  ret = pSoundTouch->receiveSamples(short_sound_array_buf, size/channel);
  for ( i=0; i<size ; i++ ){
    array[i] = (int)short_sound_array_buf[i];
  }
  return ret ;
}

int flushSoundTouch(){
  return pSoundTouch->flush();
}

int init(){
  setParamSoundTouch(8000,1,1.0f,1.0f,1.0f);
  flushSoundTouch();
  return 0;
}

