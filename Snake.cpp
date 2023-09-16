#include "Snake.h"


Snake::Snake(std::shared_ptr<Context>& context, float StartX,
	float StartY) 
	:SContext{ context }, StartX{ StartX }, StartY{StartY}, direction(Direction::Right), Score{ 0 },
	MoveTime{sf::Time::Zero}, MoveInterval{sf::seconds(0.1f)}, RandNum{0}, direction2(Direction::Down)
{
	srand(time(NULL));
}

void Snake::Init()
{
	sf::RectangleShape Block(sf::Vector2f(this->SContext->GridSize, this->SContext->GridSize));
	Block.setPosition(this->StartX, this->StartY);
	Block.setFillColor(sf::Color::Red);
	this->Body.push_back(Block);

	sf::RectangleShape Block2(sf::Vector2f(this->SContext->GridSize, this->SContext->GridSize));
	Block2.setPosition(0.f, 0.f);
	Block2.setFillColor(sf::Color::Green);
	this->Snake2.push_back(Block2);

	this->Food.setRadius(this->SContext->GridSize / 2);
	this->Food.setFillColor(sf::Color::Blue);
	this->FoodPos();
}

void Snake::Input()
{
	sf::Event event;

	while (this->SContext->Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->SContext->Window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::D:
				this->RandNum = rand() % 3;
				if (this->direction != Direction::Left)
				{
					this->direction = Direction::Right;
				}
				break;
			case sf::Keyboard::S:
				this->RandNum = rand() % 3;
				if (this->direction != Direction::Up)
				{
					this->direction = Direction::Down;
				}
				break;
			case sf::Keyboard::W:
				this->RandNum = rand() % 3;
				if (this->direction != Direction::Down)
				{
					this->direction = Direction::Up;
				}
				break;
			case sf::Keyboard::A:
				this->RandNum = rand() % 3;
				if (this->direction != Direction::Right)
				{
					this->direction = Direction::Left;
				}
				break;
			}
		}
	}
	switch (this->RandNum)
	{
	case 0:
		this->direction2 = Direction::Up;
	break;
	case 1:
		this->direction2 = Direction::Down;
	break;
	case 2:
		this->direction2 = Direction::Left;
	break;
	case 3:
		this->direction2 = Direction::Right;
	break;
	}
}

void Snake::Update(sf::Time Deltatime)
{
	this->MoveTime += Deltatime;
	if (this->MoveTime >= this->MoveInterval)
	{
		this->snake_Movement();
		this->snake2_Movement();

		this->snake_Collision();
		this->snake_Collision2();

		this->MoveTime = sf::Time::Zero;
	}
	
}

void Snake::Draw()
{
	sf::Text Score;
	Score.setString("Score: " + std::to_string(this->Score));
	Score.setFont(this->SContext->Font);
	Score.setPosition(this->SContext->Window->getSize().x / 2, 10);
	Score.setCharacterSize(50);

	this->SContext->Window->clear(sf::Color::Black);
	for (auto &djeno : this->Body)
	{
		this->SContext->Window->draw(djeno);
	}

	for (auto& i : this->Snake2)
	{
		this->SContext->Window->draw(i);
	}
	this->SContext->Window->draw(Score);
	this->SContext->Window->draw(this->Food);
	this->SContext->Window->display();
}

void Snake::Pause()
{
}

void Snake::Start()
{	

}

void Snake::snake_Movement()
{
	sf::Vector2f previousTailPosition = this->Body.back().getPosition();
	sf::RectangleShape Head = this->Body.front();
	sf::RectangleShape newHead = this->Body.front();

	float x = Head.getPosition().x;
	float y = Head.getPosition().y;

	switch (this->direction)
	{
	case Direction::Up:
		y -= this->SContext->GridSize;
		break;
	case Direction::Down:
		y += this->SContext->GridSize;
		break;
	case Direction::Left:
		x -= this->SContext->GridSize;
		break;
	case Direction::Right:
		x += this->SContext->GridSize;
		break;
	}

	newHead.setPosition(x, y);
	for (size_t i = 1; i < this->Body.size(); ++i)
	{
		if (newHead.getGlobalBounds().intersects(this->Body[i].getGlobalBounds()))
		{
			this->SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
		}
		if (newHead.getGlobalBounds().intersects(this->Snake2[i].getGlobalBounds()))
		{
			this->SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
		}
	}

	sf::RectangleShape tail = this->Body.back();
	tail.setPosition(previousTailPosition);
	this->Body.insert(this->Body.begin(), tail);
	this->Body.pop_back();

	this->Body.front() = newHead;
}

void Snake::snake2_Movement()
{
	sf::Vector2f previousTailPosition = this->Snake2.back().getPosition();
	sf::RectangleShape Head = this->Snake2.front();
	sf::RectangleShape newHead = this->Snake2.front();

	float x = Head.getPosition().x;
	float y = Head.getPosition().y;

	switch (this->direction2)
	{
	case Direction::Up:
		y -= this->SContext->GridSize;
		break;
	case Direction::Down:
		y += this->SContext->GridSize;
		break;
	case Direction::Left:
		x -= this->SContext->GridSize;
		break;
	case Direction::Right:
		x += this->SContext->GridSize;
		break;
	}

	newHead.setPosition(x, y);
	for (size_t i = 1; i < this->Snake2.size(); ++i)
	{
		if (newHead.getGlobalBounds().intersects(this->Body[i].getGlobalBounds()))
		{
			this->SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
		}
	}

	sf::RectangleShape tail = this->Snake2.back();
	tail.setPosition(previousTailPosition);
	this->Snake2.insert(this->Snake2.begin(), tail);
	this->Snake2.pop_back();

	this->Snake2.front() = newHead;
}

void Snake::snake_Collision()
{
	sf::RectangleShape Head = this->Body.front();
	if (Head.getPosition().x >= this->SContext->Window->getSize().x)
	{
		SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
	}
	if (Head.getPosition().x < 0)
	{
		SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
	}
	if (Head.getPosition().y >= this->SContext->Window->getSize().y)
	{
		SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
	}
	if (Head.getPosition().y < 0)
	{
		SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
	}
	if (Head.getGlobalBounds().intersects(this->Food.getGlobalBounds()))
	{
		this->AddSeg();
		this->FoodPos();
		this->Score++;
	}
}

void Snake::snake_Collision2()
{
	sf::RectangleShape& Head = this->Snake2.front();
	if (Head.getPosition().x >= this->SContext->Window->getSize().x)
	{
		Head.setPosition(0, Head.getPosition().y);
	}
	if (Head.getPosition().x < 0)
	{
		Head.setPosition(this->SContext->Window->getSize().x, Head.getPosition().y);
	}
	if (Head.getPosition().y >= this->SContext->Window->getSize().y)
	{
		Head.setPosition(Head.getPosition().x, 0);
	}
	if (Head.getPosition().y < 0)
	{
		Head.setPosition(Head.getPosition().x, this->SContext->Window->getSize().y);
	}
}

void Snake::FoodPos()
{
	int x = rand() % this->SContext->Width * this->SContext->GridSize;
	int y = rand() % this->SContext->Height * this->SContext->GridSize;

	this->Food.setPosition(x, y);
}

void Snake::AddSeg()
{
	sf::RectangleShape Tail = this->Body.back();
	sf::Vector2f TailPos = Tail.getPosition();

	sf::RectangleShape NewSeg(sf::Vector2f(this->SContext->GridSize, this->SContext->GridSize));
	NewSeg.setPosition(TailPos);
	NewSeg.setFillColor(sf::Color::Red);
	this->Body.insert(this->Body.end() - 1, NewSeg);

	sf::RectangleShape Tail2 = this->Snake2.back();
	sf::Vector2f TailPos2 = Tail2.getPosition();

	sf::RectangleShape NewSeg2(sf::Vector2f(this->SContext->GridSize, this->SContext->GridSize));
	NewSeg2.setPosition(TailPos2);
	NewSeg2.setFillColor(sf::Color::Green);
	this->Snake2.insert(this->Snake2.end() - 1, NewSeg2);
}
