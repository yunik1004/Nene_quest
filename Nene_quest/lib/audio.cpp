#include "audio.h"
#include <iostream>
#include <cstdio>

using namespace std;

Audio::Audio(char *filename) {
	isLoadSuccess = false;

	if (!parseWAV(filename)) {
		return;
	}

	device = alcOpenDevice(NULL);
	if (!device) {
		cerr << "Error: No sound device" << endl;
		return;
	}

	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context) {
		cerr << "Error: No sound context" << endl;
		return;
	}

	ALuint frequency = sampleRate;
	ALenum format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);
	if (alGetError() != AL_NO_ERROR) {
		cerr << "Error: Error GenSource" << endl;
		return;
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
		cerr << "Error: Wrong BitsPerSample" << endl;
		return;
	}

	alBufferData(buffer, format, buf, dataSize, frequency);
	if (alGetError() != AL_NO_ERROR) {
		cerr << "Error: Error loading AlBuffer" << endl;
		return;
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

	isLoadSuccess = true;
}

Audio::~Audio(void) {
	if (buf) {
		delete[] buf;
	}
	if (source) {
		alDeleteSources(1, &source);
	}
	if (buffer) {
		alDeleteBuffers(1, &buffer);
	}

	alcMakeContextCurrent(NULL);

	if (context) {
		alcDestroyContext(context);
	}
	if (device) {
		alcCloseDevice(device);
	}
}

void Audio::play(void) {
	if (!isLoadSuccess) {
		return;
	}

	alSourcePlay(source);
	if (alGetError() != AL_NO_ERROR) {
		cerr << "Error: Error playing sound" << endl;
	}
}

void Audio::setLoop(int isLoop) {
	if (!isLoadSuccess) {
		return;
	}

	alSourcei(source, AL_LOOPING, isLoop);
}

void Audio::stop(void) {
	if (!isLoadSuccess) {
		return;
	}

	alSourceStop(source);
	if (alGetError() != AL_NO_ERROR) {
		cerr << "Error: Error stopping sound" << endl;
	}
}

bool Audio::parseWAV(char *filename) {
	FILE *fp;
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		cerr << "Error: Can't find WAV file" << endl;
		return false;
	}

	char type[5];
	DWORD size, chunkSize;
	short formatType;
	DWORD avgBytesPerSec;
	short bytesPerSample;

	type[4] = '\0';
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "RIFF") != 0) {
		cerr << "Error: Not RIFF" << endl;
		return false;
	}
	fread(&size, sizeof(DWORD), 1, fp);
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "WAVE") != 0) {
		cerr << "Error: Not WAVE" << endl;
		return false;
	}
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "fmt ") != 0) {
		cerr << "Error: Not fmt" << endl;
		return false;
	}
	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);
	if (fread(type, sizeof(char), 4, fp) != 4 || strcmp(type, "data") != 0) {
		cerr << "Error: Missing data" << endl;
		return false;
	}
	fread(&dataSize, sizeof(DWORD), 1, fp);

	buf = new BYTE[dataSize];
	fread(buf, sizeof(BYTE), dataSize, fp);

	fclose(fp);

	return true;
}
