#pragma once

#include <SDL.h>

namespace Essentials
{
	class Screen
	{
	public:
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;

		Uint32 DefaultColor;

	private:
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_Texture *_texture;
		Uint32 *_buffer;
		SDL_Event _event;

	public:
		Screen();
		bool Init(Uint32 color);
		bool ProcessEvents();
		void ClearScreen();
		void ClearScreen(Uint32 color);
		void SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 Alpha = 0xFF);
		void SetPixel(int x, int y, Uint32 color);
		void Update();
		void Close();
	};
}


