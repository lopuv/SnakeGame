#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Snakestate.h"
#include "GameOver.h"
#include "Game.h"

enum Direction{Up, Down, Left, Right};

class Snake : public Snakestate
{
private:
	std::shared_ptr<Context> SContext;

	std::vector<sf::RectangleShape> Body;

	std::vector<sf::RectangleShape> Snake2;

	Direction direction;

	Direction direction2;

public:
	Snake(std::shared_ptr<Context>& context, 
		float StartX, float StartY);

	float StartX;
	float StartY;

	int RandNum;

	int Score;

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
	void snake2_Movement();

	void snake_Collision();
	void snake_Collision2();

	void FoodPos();

	void AddSeg();
};

