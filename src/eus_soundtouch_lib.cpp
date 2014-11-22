
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
  int setParamSoundTouch(int samplerate, int channel, double tempo, double pitch, double rate){
    std::cout << "[setParamSoundTouch]" << std::endl;
    std::cout << "  samplerate: " << samplerate << std::endl;
    std::cout << "  channel   : " << channel << std::endl;
    std::cout << "  tempo     : " << tempo << std::endl;
    std::cout << "  pitch     : " << pitch << std::endl;
    std::cout << "  rate      : " << rate << std::endl;
    pSoundTouch->setSampleRate(samplerate);
    pSoundTouch->setChannels(channel);
    pSoundTouch->setTempoChange((float)tempo);
    pSoundTouch->setPitchSemiTones((float)pitch);
    pSoundTouch->setRateChange((float)rate);
    //pSoundTouch->setSetting(SETTING_USE_QUICKSEEK, 0);
    //pSoundTouch->setSetting(SETTING_USE_AA_FILTER, 1);
    //pSoundTouch->setSetting(0, 0);
    //pSoundTouch->setSetting(1, 1);
    return 1;
  }
}

extern "C" {
  int putSampleSoundTouch(double* array, int size, int channel){
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
  int receiveSampleSoundTouch(double* array, int size, int channel){
    int i ,ret;
    checkSizeOfBuffer(size);
    ret = pSoundTouch->receiveSamples(short_sound_array_buf, size/channel);
    for ( i=0; i<size ; i++ ){
      array[i] = (double)short_sound_array_buf[i];
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
  void openInWavFile(char *file_name, double* buf) {
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
  int readWavFile(double* buffer, int size){
    return _readWavFile(inFile, buffer, size);
  }
}

extern "C"{
  void writeWavFile(double* buffer, int size){
    return _writeWavFile(outFile, buffer, size);
  }
}
