#include "Game.h"
#include "MainMenu.h"

Game::Game()
	:GContext{std::make_shared<Context>()}
{
	srand(time(nullptr));
	this->GContext->Window->create(sf::VideoMode(800, 600), "Snake game");
	this->GContext->Window->setFramerateLimit(144);
	this->GContext->States->AddState(std::make_unique<MainMenu>(GContext));
}

void Game::Run()
{
	while (this->GContext->Window->isOpen())
	{
		this->GContext->States->ProcessStateChange();
		this->GContext->States->GetCurrent()->Input();
		this->GContext->States->GetCurrent()->Update(TIME_PER_FRAME);
		this->GContext->States->GetCurrent()->Draw();
	}
}