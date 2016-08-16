#include <SDL.h>
#include <math.h>
#include <iostream>
#include "Screen.h"
#include "Bullet.h"

using namespace std;
using namespace Essentials;
using namespace Gameplay;

float velocity[2] = { 0, 0 };

static Uint32* ReadBmp(char* filename, int &width, int &height)
{
	//int i;
	FILE* fileStream;
	errno_t err = fopen_s(&fileStream, filename, "rb");
	Uint8 fileInfo[54];

	if (fileStream == nullptr)
	{
		cout << "File open Error   " << err << endl;
		return nullptr;
	}
	fread(fileInfo, sizeof(Uint8), 54, fileStream);

	int fileWidth = *(int*)&fileInfo[18];
	int fileHeight = *(int*)&fileInfo[22];

	int size = fileWidth * fileHeight;
	int rowPadded = (fileWidth * 3 + 3) & (~3);

	Uint8 *buffer = new Uint8[rowPadded];
	//fread(buffer, sizeof(Uint8), size * 3, fileStream);

	Uint32 *data = new Uint32[size];
	for (int i = fileHeight - 1; i >= 0; --i)
	{
		fread(buffer, sizeof(Uint8), rowPadded, fileStream);
		for (int ii = 0; ii < fileWidth * 3; ii += 3)
		{
			Uint32 temp = 0;

			temp += buffer[ii + 2];
			temp <<= 8;
			temp += buffer[ii + 1];
			temp <<= 8;
			temp += buffer[ii];
			temp <<= 8;
			temp += 0xFF;
			//	cout << "R: " << (int)buffer[ii + 2] << " G: " << (int)buffer[ii + 1] << " B: " << (int)buffer[ii] << ii/3 << endl;
			data[(i * fileWidth) + (ii / 3)] = temp;
		}
	}
	delete[] buffer;
	fclose(fileStream);

	width = fileWidth;
	height = fileHeight;

	//int temp, i, count = size;
	//for (i = 0; i < count / 2; ++i) {
	//	temp = data[count - i - 1];
	//	data[count - i - 1] = data[i];
	//	data[i] = temp;
	//}

	return data;
}

void ProcessKeyboard(const Uint8* keyboardState, Screen screen) {

	if (keyboardState[SDL_SCANCODE_RIGHT] == 1)
	{
		velocity[0] = 5;
		//_RPT1(0, "2 released\n", 0);
	}
	else
	{
		velocity[0] = 0;
	}
	if (keyboardState[SDL_SCANCODE_LEFT] == 1)
	{
		if (velocity[0] > 0)
		{
			velocity[0] = 0;
		}
		else
		{
			velocity[0] = -5;
		}
		
		//_RPT1(0, "2 released\n", 0);
	}
	else
	{
		if (velocity[0] < 0)
		{
			velocity[0] = 0;
		}
	}

	if (keyboardState[SDL_SCANCODE_DOWN] == 1)
	{
		velocity[1] = 5;
	}
	else
	{
		velocity[1] = 0;
	}

	if (keyboardState[SDL_SCANCODE_UP] == 1)
	{
		if (velocity[1] > 0)
		{
			velocity[1] = 0;
		}
		else
		{
			velocity[1] = -5;
		}
	}

	if (keyboardState[SDL_SCANCODE_Y] == 1)
	{
		screen.ClearScreen();
	}
}

int MainProgram()
{
	Screen screen;

	if (screen.Init(0xFFFF00FF) == false)
	{
		std::cout << "Init went wrong" << endl;
		return 1;
	}

	int playerWidth, playerHeight, bulletWidth, bulletHeight;
	Uint32 *imageData = ReadBmp("P:\\My Documents\\Visual Studio 2013\\Projects\\SDLGame\\Debug\\firefox.bmp", playerWidth, playerHeight);
	Uint32 *bulletImage = ReadBmp("P:\\My Documents\\Visual Studio 2013\\Projects\\SDLGame\\Debug\\AimReticle3.bmp", bulletWidth, bulletHeight);
	int elapsed;
	
	float position[2] = { 0, 0 };
	{
		float bulletPos[2] = { 0, 0 };
		float bulletSize[2] = { bulletWidth, bulletHeight };
		Bullet bullet(bulletPos, bulletImage, );

	}

	while (true)
	{
		
		const Uint8* newKeyboardState = SDL_GetKeyboardState(NULL);
		
		if (screen.ProcessEvents() == false)
			break;

		ProcessKeyboard(newKeyboardState, screen);
		elapsed = SDL_GetTicks();

		for (int y = 0; y < screen.SCREEN_HEIGHT; ++y)
		{
			for (int x = 0; x < screen.SCREEN_WIDTH; ++x)
			{
				//screen.SetPixel(x, y, (sin(elapsed / 1000.0) + 1) * 127, sin(((elapsed / 1000.0 + 50) * 2) + 1) * 127, sin(((elapsed / 1000.0 + 120) * 3) + 1) * 127);
			}
		}

		if (imageData == nullptr)
			break;

		position[0] += velocity[0];
		position[1] += velocity[1];

		if (position[1] < 0)
		{
			position[1] = 0;
		}
		else if (position[1] + playerHeight > screen.SCREEN_HEIGHT)
		{
			position[1] = (float)(screen.SCREEN_HEIGHT - playerHeight);
		}
		if (position[0] < 0)
		{
			position[0] = 0;
		}
		else if (position[0] + playerWidth > screen.SCREEN_WIDTH)
		{
			position[0] = (float)(screen.SCREEN_WIDTH - playerWidth);
		}

		for (int y = 0; y < playerHeight; ++y)
		{
			for (int x = 0; x < playerWidth; ++x)
			{
				screen.SetPixel(x + (int)position[0], y + (int)position[1], imageData[(y * playerWidth) + x]);
			}
		}

		screen.Update();
	}
	delete[] imageData;
	screen.Close();
	return 0;
}



int main(int argc, char* argv[])
{
	int errorCode;
	errorCode = MainProgram();

	//system("pause");
	return errorCode;
}



