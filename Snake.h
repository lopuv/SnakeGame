#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Snake
{
public:
	Snake(sf::Vector2f size);

	sf::Vector2f Size;
	std::vector<sf::RectangleShape> Segments;

	std::vector<sf::RectangleShape>::iterator head;
	std::vector<sf::RectangleShape>::iterator tail;

	sf::Vector2f SnakeDir;
	sf::Vector2f newDir;

	int Score;
	bool Self_collision;

	void AddSegment(sf::Vector2f& Dir);
	void Move(const sf::Vector2f& Dir);
	int Collision();
	bool Collision(sf::Sprite& sprite);


};

