#include "Snake.h"


Snake::Snake(std::shared_ptr<Context>& context) 
	:Size(50.f, 50.f), SnakeDir{1},
	Segments{}, SContext{context}, Score{0}, Self_collision{false}, 
	MoveTime{ sf::Time::Zero }, MoveInterval{ sf::seconds(0.1f) }, Food{50.f}
{
	this->Init();
}

void Snake::Init()
{
	this->Segments.push_back(std::shared_ptr<sf::Vector2i>(new sf::Vector2i(this->SContext->Width / 2, this->SContext->Height / 2)));
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
				this->ChangeDir(1);
				break;
			case sf::Keyboard::S:
				this->ChangeDir(2);
				break;
			case sf::Keyboard::W:
				this->ChangeDir(4);
				break;
			case sf::Keyboard::A:
				this->ChangeDir(3);
				break;
			}
		}
	}
}

void Snake::Update(sf::Time Deltatime)
{
	this->MoveTime += Deltatime;
	if (this->MoveTime >= this->MoveInterval)
	{
		this->snake_Movement();
		this->MoveTime = sf::Time::Zero;
	}
}

void Snake::Draw()
{
	this->SContext->Window->clear();
	for (auto& djeno : this->Segments)
	{
		sf::RectangleShape Shape(sf::Vector2f(this->SContext->GridSize, this->SContext->GridSize));
		Shape.setPosition(djeno.get()->x * this->SContext->GridSize, djeno.get()->y * SContext->GridSize);
		Shape.setFillColor(sf::Color::Red);
		this->snake_Collision(Shape);
		this->SContext->Window->draw(Shape);
	}
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
	std::shared_ptr<sf::Vector2i> NewPos = this->Segments[0];
	switch (this->SnakeDir)
	{
		{
	case 1: //Right
		NewPos.get()->x++;
	break;
	case 2: //Down
		NewPos.get()->y++;
	break;
	case 3: //Left
		NewPos.get()->x--;
	break;
	case 4: //Up
		NewPos.get()->y--;
	break;
		}
	}
	for (int cum = this->Segments.size() - 1; cum > 0; --cum)
	{
		this->Segments[cum] = this->Segments[cum - 1];
	}

	this->Segments[0] = NewPos;
}

void Snake::snake_Collision(sf::RectangleShape& rect)
{
	if (rect.getPosition().x >= this->SContext->Window->getSize().x)
	{
		SContext->States->AddState(std::make_unique<GameOver>(SContext), true);
	} 
	if (rect.getPosition().x < 0)
	{
		rect.setPosition(0, rect.getPosition().y);
	}
	if (rect.getPosition().y >= this->SContext->Window->getSize().y)
	{
		rect.setPosition(this->SContext->Window->getSize().x, rect.getPosition().y);
	}
	if (rect.getPosition().y < 0)
	{
		this->ChangeDir(2);
	} 



}




void Snake::ChangeDir(int NewDir)
{
	if (NewDir >= 1 && NewDir <= 4)
	{
		if (std::abs(this->SnakeDir - NewDir) != 2)
		{
			this->SnakeDir = NewDir;
		}
	}
}

