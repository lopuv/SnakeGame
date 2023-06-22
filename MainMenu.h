#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Snakestate.h"
#include "Game.h"
#include "GamePlay.h"

class MainMenu : public Snakestate
{
private:
	sf::Text GameTitle;
	sf::Text PlayButton;
	sf::Text ExitButton;

	bool PlayButtonPressed;
	bool PlayButtonSelected;
	bool ExitButtonSelected;
	bool ExitButtonPressed;

	std::shared_ptr<Context> MContext;

public:
	MainMenu(std::shared_ptr<Context>& Mcontext);
	~MainMenu();

	void Init()override;
	void Input()override;
	void Update(sf::Time deltatime) override;
	void Draw() override;
};

