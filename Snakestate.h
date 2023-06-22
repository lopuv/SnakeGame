#pragma once
#include <SFML/Graphics.hpp>

class Snakestate
{
public:
	Snakestate() {};
	virtual ~Snakestate() {};

	virtual void Init() = 0;
	virtual void Input() = 0;

	virtual void Update(sf::Time Deltatime) = 0;
	virtual void Draw() = 0;

	virtual void Pause() {};
	virtual void Start() {};
};