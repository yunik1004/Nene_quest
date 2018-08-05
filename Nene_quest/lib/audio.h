#pragma once

#include <AL/al.h>
#include <AL/alc.h>

typedef unsigned int DWORD;
typedef unsigned char BYTE;

class Audio {
private:
	short channels;
	DWORD sampleRate;
	short bitsPerSample;
	DWORD dataSize;
	BYTE *buf;
	ALCdevice *device;
	ALCcontext *context;
	ALuint source;
	ALuint buffer;
	bool isLoadSuccess;
	bool parseWAV(char *);
public:
	Audio(char *);
	~Audio(void);
	void setLoop(int);
	void play(void);
	void stop(void);
};
