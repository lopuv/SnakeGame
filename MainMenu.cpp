#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<Context>& context)
	:MContext{context}, PlayButtonSelected{true},
	PlayButtonPressed{false}, ExitButtonSelected{false},
	ExitButtonPressed{false}
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    // Title
    this->GameTitle.setFont(MContext->Font);
    this->GameTitle.setString("Snake");
    this->GameTitle.setOrigin(GameTitle.getLocalBounds().width / 2, GameTitle.getLocalBounds().height / 2);
    this->GameTitle.setPosition(MContext->Window->getSize().x / 2, MContext->Window->getSize().y / 2 - 100.f);

    // Play button
    this->PlayButton.setFont(MContext->Font);
    this->PlayButton.setString("Play");
    this->PlayButton.setOrigin(PlayButton.getLocalBounds().width / 2, PlayButton.getLocalBounds().height / 2);
    this->PlayButton.setPosition(MContext->Window->getSize().x / 2, MContext->Window->getSize().y / 2 - 25.f);
    this->PlayButton.setCharacterSize(20);

    // exit button
    this->ExitButton.setFont(MContext->Font);
    this->ExitButton.setString("Exit");
    this->ExitButton.setOrigin(ExitButton.getLocalBounds().width / 2, ExitButton.getLocalBounds().height / 2);
    this->ExitButton.setPosition(MContext->Window->getSize().x / 2, MContext->Window->getSize().y / 2 + 25.f);
    this->ExitButton.setCharacterSize(20);
}

void MainMenu::Input()
{
	sf::Event event;
	while (this->MContext->Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->MContext->Window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!PlayButtonSelected)
                {
                    PlayButtonSelected = true;
                    ExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!ExitButtonSelected)
                {
                    PlayButtonSelected = false;
                    ExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                ExitButtonPressed = false;
                PlayButtonPressed = false;
                if (ExitButtonSelected)
                {
                    ExitButtonPressed = true;
                }
                else
                {
                    PlayButtonPressed = true;
                }
                break;
            }
            default:
            {
                break;
            }
            }
		}
	}
}

void MainMenu::Update(sf::Time deltatime)
{
    if (PlayButtonSelected)
    {
        PlayButton.setFillColor(sf::Color::Green);
        ExitButton.setFillColor(sf::Color::White);
    }
    else
    {
        ExitButton.setFillColor(sf::Color::Green);
        PlayButton.setFillColor(sf::Color::White);
    }

    if (PlayButtonPressed)
    {
        MContext->States->AddState(std::make_unique<Snake>(MContext, 400, 300), true);
    }
    else if (ExitButtonPressed)
    {
        MContext->Window->close();
    }
}

void MainMenu::Draw()
{
    MContext->Window->clear();
    MContext->Window->draw(GameTitle);
    MContext->Window->draw(PlayButton);
    MContext->Window->draw(ExitButton);
    MContext->Window->display();
}
