#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Snakestate.h"
#include "GameOver.h"
#include "Game.h"

class Snake : public Snakestate
{
private:
	std::shared_ptr<Context> SContext;

public:
	Snake(std::shared_ptr<Context>& context);

	sf::Vector2f Size;
	std::vector<std::shared_ptr<sf::Vector2i>> Segments;

	int SnakeDir;

	int Score;
	bool Self_collision;

	sf::Time MoveTime;
	sf::Time MoveInterval;

	sf::CircleShape Food;

	void Init() override;
	void Input() override;
	void Update(sf::Time Deltatime) override;
	void Draw() override;
	void Pause() override;
	void Start() override;

	void snake_Movement();
	void snake_Collision(sf::RectangleShape& rect);

	void ChangeDir(int NewDir);
	
};

