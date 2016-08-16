#pragma once

#include <SDL.h>
#include "Screen.h"

namespace Gameplay{
	class Bullet
	{
	public:
		float position[2];
		Uint32 *texture;
		int textureSize[2];

	public:
		Bullet(float inputPosition[2], Uint32 *inputTexture, int inputTexSize[2]);
		void Draw(Essentials::Screen screen);
		//~Bullet();
	};

}

