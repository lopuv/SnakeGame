#include "GameOver.h"

GameOver::GameOver(std::shared_ptr<Context>& context)
	:GOContext{context}, PlayAgainSelected{true},
	PlayAgainPressed{false}, ExitSelected{false},
	ExitPressed{false}
{
	this->Init();
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	this->Text.setFont(this->GOContext->Font);
	this->Text.setString("GAME OVER");
	this->Text.setOrigin(this->Text.getLocalBounds().width / 2, this->Text.getLocalBounds().height / 2);
	this->Text.setPosition(this->GOContext->Window->getSize().x / 2, this->GOContext->Window->getSize().y / 2 - 100.f);
	this->Text.setCharacterSize(20);

	this->PlayAgain.setFont(this->GOContext->Font);
	this->PlayAgain.setString("Play Again");
	this->PlayAgain.setOrigin(this->PlayAgain.getLocalBounds().width / 2, this->PlayAgain.getLocalBounds().height / 2);
	this->PlayAgain.setPosition(this->GOContext->Window->getSize().x / 2, this->GOContext->Window->getSize().y / 2 - 25.f);
	this->PlayAgain.setCharacterSize(20);

	this->Exit.setFont(this->GOContext->Font);
	this->Exit.setString("Exit");
	this->Exit.setOrigin(this->Exit.getLocalBounds().width / 2, this->Exit.getLocalBounds().height / 2);
	this->Exit.setPosition(this->GOContext->Window->getSize().x / 2, this->GOContext->Window->getSize().y / 2 + 25.f);
	this->Exit.setCharacterSize(20);
}

void GameOver::Input()
{
	sf::Event event;
	while (this->GOContext->Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->GOContext->Window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (!PlayAgainSelected)
				{
					PlayAgainSelected = true;
					ExitSelected = false;
				}
				break;
			case sf::Keyboard::Down:
				if (!ExitSelected)
				{
					PlayAgainSelected = false;
					ExitSelected = true;
				}
				break;
			case sf::Keyboard::Return:
				ExitPressed = false;
				PlayAgainPressed = false;
				if (ExitSelected)
				{
					ExitPressed = true;
				}
				else
				{
					PlayAgainPressed = true;
				}
				break;
			}
		}
	}
}

void GameOver::Update(sf::Time Deltatime)
{
	if (PlayAgainSelected)
	{
		PlayAgain.setFillColor(sf::Color::Green);
		Exit.setFillColor(sf::Color::White);
	}
	else
	{
		Exit.setFillColor(sf::Color::Green);
		PlayAgain.setFillColor(sf::Color::White);
	}

	if (PlayAgainPressed)
	{
		this->GOContext->States->AddState(std::make_unique<Snake>(GOContext), true);
	}
	else if (ExitPressed)
	{
		this->GOContext->Window->close();
	}
}

void GameOver::Draw()
{
	this->GOContext->Window->clear();
	this->GOContext->Window->draw(Text);
	this->GOContext->Window->draw(PlayAgain);
	this->GOContext->Window->draw(Exit);
	this->GOContext->Window->display();
}
