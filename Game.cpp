#include "Game.h"
#include "MainMenu.h"

Game::Game()
	:GContext{std::make_shared<Context>()}, Clock{}
{
	srand(time(nullptr));
	this->GContext->Window->create(sf::VideoMode(this->GContext->Width * this->GContext->GridSize,
		this->GContext->Height * this->GContext->GridSize), "Snake game");
	this->GContext->Window->setFramerateLimit(144);
	this->GContext->States->AddState(std::make_unique<MainMenu>(GContext));
}

void Game::Run()
{
	while (this->GContext->Window->isOpen())
	{
		this->GContext->States->ProcessStateChange();
		this->GContext->States->GetCurrent()->Input();
		this->GContext->States->GetCurrent()->Update(this->Clock.restart());
		this->GContext->States->GetCurrent()->Draw();
	}
}


