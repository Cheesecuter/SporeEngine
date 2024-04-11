#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <iostream>
#include <conio.h>
#include <math.h>

int main1(int argc, char** argv)
{
	bool paused = false, stopped = false;

	alutInit(&argc, argv);

	ALuint source;
	alGenSources(1, &source);

	//ALuint buffer = alutCreateBufferFromFile("./Assets/Audios/Accidents_Will_Happen.wav");
	ALuint buffer = alutCreateBufferFromFile("./Assets/Audios/Accidents_Will_Happen.wav");

	alSourcei(source, AL_BUFFER, buffer);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcei(source, AL_LOOPING, AL_TRUE);

	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_POSITION, 100, 0, 100);

	alSourcePlay(source);

	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		std::cerr << "Error occurred: " << alGetString(error) << std::endl;
		return 1;
	}

	//while (!_kbhit())
	//{
	//	double theta = (double) (rand() % 360) * 3.14 / 180.0;
	//	ALfloat x = -float(cos(theta));
	//	ALfloat y = -float(rand() % 2);
	//	ALfloat z = -float(sin(theta));
	//	alSource3f(source, AL_POSITION, 10, y, z);
	//	//alListener3f(AL_POSITION, x, y, z);

	//	//static float listenerPosition = 0.0f;
	//	//listenerPosition += 1.0f;
	//	//alListener3f(AL_POSITION, 0.0f, 0.0f, listenerPosition);
	//}

	ALint source_state;
	while (!stopped)
	{
		double theta = (double) (rand() % 360) * 3.14 / 180.0;
		ALfloat x = -float(cos(theta));
		ALfloat y = -float(rand() % 2);
		ALfloat z = -float(sin(theta));
		alSource3f(source, AL_POSITION, x, y, z);
		alutSleep(0.5);
		/*alGetSourcei(source, AL_SOURCE_STATE, &source_state);
		if (source_state != AL_PLAYING)
		{
			stopped = true;
		}*/
		if (_kbhit())
		{
			char key = _getch();
			if (key == 'p' || key == 'P')
			{
				if (!paused)
				{
					alSourcePause(source);
					paused = true;
				}
				else
				{
					alSourcePlay(source);
					paused = false;
				}
			}
			else if (key == 's' || key == 'S')
			{
				alSourceStop(source);
				stopped = true;
			}
		}
	}

	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	if (source_state != AL_PLAYING)
	{
		stopped = true;
	}

	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);

	alutExit();

	return 0;
}