#include "Demo.h"

void Demo::InitAudio() {
	int flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (flags != Mix_Init(flags)) {
		
	}

	int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		
	}

	music = Mix_LoadMUS("spiderBgm.wav");
	if (music == NULL) {
		
	}

	sound = Mix_LoadWAV("grsites.com_whirls.wav");
	if (sound == NULL) {
		
	}


}