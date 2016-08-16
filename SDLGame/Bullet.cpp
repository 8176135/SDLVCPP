#include "Bullet.h"

using namespace Gameplay;

Bullet::Bullet(float inputPosition[2], Uint32 *inputTexture, int inputTexSize[2])
{
	position[0] = inputPosition[0];
	position[1] = inputPosition[1];
	texture = inputTexture;
	textureSize[0] = inputTexSize[0];
	textureSize[1] = inputTexSize[1];
}

void Bullet::Draw(Essentials::Screen screen)
{
	for (int y = 0; y < textureSize[1]; ++y)
	{
		for (int x = 0; x < textureSize[0]; ++x)
		{
			screen.SetPixel(x + (int)position[0], y + (int)position[1], texture[(y * textureSize[0]) + x]);
		}
	}
}


//Bullet::~Bullet()
//{
//}
