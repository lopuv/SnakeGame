#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Snakebasket.h"

struct Context
{
	std::unique_ptr<Snakebasket> States;
	std::unique_ptr<sf::RenderWindow> Window;
	sf::Font Font;
	int GridSize;
	int Width;
	int Height;
	int dt;


	Context()
		:GridSize{50}, Width{30}, Height{20}
	{
		States = std::make_unique<Snakebasket>();
		Window = std::make_unique<sf::RenderWindow>();
		if (!Font.loadFromFile("arial.ttf"))
		{
			std::cout << "font could not be loaded " << std::endl;
		}
	}
};

class Game
{
private:
	std::shared_ptr<Context> GContext;
	sf::Clock Clock;

	const sf::Time TIME_PER_FRAME = sf::seconds(1.0f / 60.f);

public:
	Game();

	void Run();
};

