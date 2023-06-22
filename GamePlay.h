#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Snakestate.h"

class GamePlay : public Snakestate
{
private:
	std::shared_ptr<Context> GPContext;

	bool Paused;
	sf::Event Event;

	sf::Clock Clock;
	float Dt;
	int Fps;

public:
	GamePlay(std::shared_ptr<Context>& context);

	void Init() override;
	void Input() override;
	void Update(sf::Time deltatime) override;
	void Draw() override;
	void Pause() override;
	void Start() override;

	~GamePlay();

};

