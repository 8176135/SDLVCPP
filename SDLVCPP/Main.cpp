#include <SDL.h>
#include <math.h>
#include <iostream>
#include "Screen.h"

using namespace std;
using namespace Essentials;

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



int MainProgram()
{
	Screen screen;

	if (screen.Init(0xFFFF00FF) == false)
	{
		std::cout << "Init went wrong" << endl;
		return 1;
	}

	int width, height;
	Uint32 *imageData = ReadBmp("F:\\Documents\\Visual Studio 2015\\Projects\\SimpleMediaTry1\\x64\\Debug\\AimReticle2.bmp", width, height);
	int elapsed;

	while (true)
	{
		if (screen.ProcessEvents() == false)
			break;

		elapsed = SDL_GetTicks();

		for (int y = 0; y < screen.SCREEN_HEIGHT; ++y)
		{
			for (int x = 0; x < screen.SCREEN_WIDTH; ++x)
			{
				screen.SetPixel(x, y, (sin(elapsed / 1000.0) + 1) * 127, sin(((elapsed / 1000.0 + 50) * 2) + 1) * 127, sin(((elapsed / 1000.0 + 120) * 3) + 1) * 127);
			}
		}

		if (imageData == nullptr)
			break;

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				screen.SetPixel(x + elapsed / 10, y + elapsed / 10, imageData[(y * width) + x]);
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

	system("pause");
	return errorCode;
}



