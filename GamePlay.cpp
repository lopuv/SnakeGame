#include "GamePlay.h"

GamePlay::GamePlay(std::shared_ptr<Context>& context)
	:GPContext{context}, Paused{false}, Event{}, Clock{}, Dt{0.f}, Fps{0}
{
	srand(time(nullptr));
}

void GamePlay::Init()
{
	//init snake and stuff
}

void GamePlay::Input()
{
}

void GamePlay::Update(sf::Time deltatime)
{
}

void GamePlay::Draw()
{
}

void GamePlay::Pause()
{
}

void GamePlay::Start()
{
}

GamePlay::~GamePlay()
{
}
