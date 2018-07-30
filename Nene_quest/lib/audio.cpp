#include "audio.h"
#include <iostream>
#include <cstdio>

using namespace std;

Audio::Audio(char *filename) {
	parseWAV(filename);

	device = alcOpenDevice(NULL);
	if (!device) {
		exitWithError("No sound device");
	}

	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context) {
		exitWithError("No sound context");
	}

	ALuint frequency = sampleRate;
	ALenum format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);
	if (alGetError() != AL_NO_ERROR) {
		exitWithError("Error GenSource");
	}

	if (bitsPerSample == 8) {
		if (channels == 1) {
			format = AL_FORMAT_MONO8;
		}
		else if (channels == 2) {
			format = AL_FORMAT_STEREO8;
		}
	}
	else if (bitsPerSample == 16) {
		if (channels == 1) {
			format = AL_FORMAT_MONO16;
		}
		else if (channels == 2) {
			format = AL_FORMAT_STEREO16;
		}
	}

	if (!format) {
		exitWithError("Wrong BitsPerSample");
	}

	alBufferData(buffer, format, buf, dataSize, frequency);
	if (alGetError() != AL_NO_ERROR) {
		exitWithError("Error loading AlBuffer");
	}

	/* Sound setting variables */
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

	/* Listener */
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

	/* Source */
	alSourcei(source, AL_BUFFER, buffer);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSourcefv(source, AL_POSITION, SourcePos);
	alSourcefv(source, AL_VELOCITY, SourceVel);
	alSourcei(source, AL_LOOPING, AL_FALSE);
}

Audio::~Audio(void) {
	delete[] buf;
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void Audio::play(void) {
	alSourcePlay(source);
	if (alGetError() != AL_NO_ERROR) {
		exitWithError("Error playing sound");
	}
}

void Audio::setLoop(int isLoop) {
	alSourcei(source, AL_LOOPING, isLoop);
}

void Audio::stop(void) {
	alSourceStop(source);
	if (alGetError() != AL_NO_ERROR) {
		exitWithError("Error stopping sound");
	}
}

void Audio::parseWAV(char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		exitWithError("Can't find WAV file");
	}

	char type[5];
	DWORD size, chunkSize;
	short formatType;
	DWORD avgBytesPerSec;
	short bytesPerSample;

	type[4] = '\0';
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "RIFF") != 0) {
		exitWithError("Not RIFF");
	}
	fread(&size, sizeof(DWORD), 1, fp);
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "WAVE") != 0) {
		exitWithError("Not WAVE");
	}
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "fmt ") != 0) {
		exitWithError("Not fmt");
	}
	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "data") != 0) {
		exitWithError("Missing data");
	}
	fread(&dataSize, sizeof(DWORD), 1, fp);

	buf = new BYTE[dataSize];
	fread(buf, sizeof(BYTE), dataSize, fp);

	fclose(fp);
}

void Audio::exitWithError(char *msg) {
	cerr << "Error: " << msg << endl;
	exit(EXIT_FAILURE);
}
