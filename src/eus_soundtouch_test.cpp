
#include <iostream>
#include <soundtouch/SoundTouch.h>

using namespace soundtouch;

int main(){

  soundtouch::SoundTouch soundTouch;
  soundtouch::SoundTouch* pSoundTouch = &soundTouch;

  pSoundTouch->setSampleRate(8000);
  pSoundTouch->setChannels(1);
  pSoundTouch->setTempoChange(1.0f);
  pSoundTouch->setPitchSemiTones(1.0f);
  pSoundTouch->setRateChange(1.0f);

  // pSoundTouch->setSetting(SETTING_USE_QUICKSEEK, params->quick);
  // pSoundTouch->setSetting(SETTING_USE_AA_FILTER, !(params->noAntiAlias));
  pSoundTouch->setSetting(SETTING_SEQUENCE_MS, 40);
  pSoundTouch->setSetting(SETTING_SEEKWINDOW_MS, 15);
  pSoundTouch->setSetting(SETTING_OVERLAP_MS, 8);

  int BUFSIZE=1024;
  SAMPLETYPE sampleBuffer[BUFSIZE];

  pSoundTouch->putSamples(sampleBuffer, BUFSIZE/1);
  while ( 0 != pSoundTouch->receiveSamples(sampleBuffer, BUFSIZE/1) );

  pSoundTouch->flush();

  return 0;
}

