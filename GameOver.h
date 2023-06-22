#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Snakestate.h"
#include "Game.h"
#include "Snake.h"

class GameOver : public Snakestate
{
private:
	sf::Text Text;
	sf::Text PlayAgain;
	sf::Text Exit;

	bool PlayAgainPressed;
	bool PlayAgainSelected;
	bool ExitPressed;
	bool ExitSelected;

	std::shared_ptr<Context> GOContext;

public:
	GameOver(std::shared_ptr<Context>& GOContext);
	~GameOver();

	void Init() override;
	void Input() override;
	void Update(sf::Time Deltatime) override;
	void Draw() override;
};

