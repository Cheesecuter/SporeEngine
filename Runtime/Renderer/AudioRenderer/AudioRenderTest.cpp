#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <iostream>

int main(int argc, char** argv)
{
	alutInit(&argc, argv);

	ALCdevice* device = alcOpenDevice(NULL);
	if (device != NULL)
	{
		ALCcontext* context = alcCreateContext(device, NULL);
		if (context != NULL)
		{
			alcMakeContextCurrent(context);

			ALuint buffer;
			alGenBuffers(1, &buffer); 
			//buffer = alutCreateBufferFromFile("./Assets/Audios/ES_Maximum High 3 - Jack Elphick.wav");
			//buffer = alutCreateBufferFromFile("D:/SporeEngine/master/SporeEngine/Assets/Audios/ES_Maximum High 3 - Jack Elphick.wav");
			buffer = alutCreateBufferFromFile("D:/SporeEngine/master/SporeEngine/Assets/Audios/helloworld.wav");
			ALuint source;
			alGenSources(1, &source);
			alSourcei(source, AL_BUFFER, buffer);
			alSourcef(source, AL_GAIN, 0.8f);

			alSourcePlay(source);
			ALint state;
			do
			{
				alGetSourcei(source, AL_SOURCE_STATE, &state);
			}
			while (state == AL_PLAYING);

			//alSourceStop(source);

			alDeleteSources(1, &source);

			alDeleteBuffers(1, &buffer);

			alcDestroyContext(context);
		}

		alcCloseDevice(device);
	}

	return 0;
}