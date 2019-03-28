#include "Game.h"
#include "TextureManager.h"
#include "Map.h"

#include "Components.h"
#include "ECS.h"

Map* map;


SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initalised!..." << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!..." << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map();
	
	//ecs implem

	player.addComponent<PositionComponent>(200, 500);
	player.addComponent<SpriteComponent>("assets/WizardPNG.png");
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	if (player.getComponent<PositionComponent>().x() > 100)
	{
		player.getComponent<SpriteComponent>().setTex("assets/WizardPNG2.png");
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//this is where we add stuff to render
	map->DrawMap();
	manager.draw();
	//
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!..." << std::endl;
}