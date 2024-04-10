#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <iostream>
#include <conio.h>

int main(int argc, char** argv)
{
	bool paused = false, stopped = false;

	alutInit(&argc, argv);

	ALuint source;
	alGenSources(1, &source);

	ALuint buffer = alutCreateBufferFromFile("D:/SporeEngine/master/SporeEngine/Assets/Audios/Accidents_Will_Happen.wav");

	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);

	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		std::cerr << "Error occurred: " << alGetString(error) << std::endl;
		return 1;
	}

	while (!stopped)
	{
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

	ALint source_state;
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