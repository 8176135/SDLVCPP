#include "Screen.h"
#include <cstring>
#include <iostream>


namespace Essentials
{
	Screen::Screen()
	{
		_window = nullptr;
		_renderer = nullptr;
		_texture = nullptr;
		_buffer = nullptr;
	}

	bool Screen::Init(Uint32 color)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			//std::cout << "SDL init Failed :(" << std::endl;
			return false;
		}

		//std::cout << "SDL Init Worked!!!" << std::endl;
		_window = SDL_CreateWindow("IT WORKED!", 300, 300, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (_window == nullptr)
		{
			SDL_Quit();
			//std::cout << "Could not create window because: " << SDL_GetError() << std::endl;
			return false;
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == nullptr)
		{
			//	std::cout << "Could not create renderer" << std::endl;
			SDL_DestroyWindow(_window);
			SDL_Quit();
			return false;
		}

		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (_texture == nullptr)
		{
			//	std::cout << "Could not create texture" << std::endl;
			SDL_DestroyRenderer(_renderer);
			SDL_DestroyWindow(_window);
			SDL_Quit();
		}

		_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; ++i)
		{
			_buffer[i] = color;
		}
		//memset(_buffer, 50, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));
		Update();

		return true;
	}

	bool Screen::ProcessEvents()
	{
		while (SDL_PollEvent(&_event))
		{
			switch (_event.type)
			{
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				std::cout << "Key press detected" << std::endl;
				if (_event.key.keysym.sym == SDLK_0)
				{
					std::cout << "0 ---" << std::endl;
				}
			case SDL_KEYUP:
				std::cout << "Key release detected" << std::endl;
				if (_event.key.keysym.sym == SDLK_2)
				{
					std::cout << "5 ---" << std::endl;
				}
			}
			//if (_event.type == SDL_QUIT)
			//{
			//	return false;
			//}
		}
		return true;
	}

	void Screen::SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
	{
		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += alpha;

		_buffer[(y*SCREEN_WIDTH) + x] = color;
	}

	void Screen::SetPixel(int x, int y, Uint32 color)
	{
		_buffer[(y*SCREEN_WIDTH) + x] = color;
	}

	void Screen::Update()
	{
		SDL_UpdateTexture(_texture, nullptr, _buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(_renderer);
		SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
		SDL_RenderPresent(_renderer);
	}

	void Screen::Close()
	{
		delete[] _buffer;
		SDL_DestroyTexture(_texture);
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}
}


