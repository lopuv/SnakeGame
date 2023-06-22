#include "Snakebasket.h"

Snakebasket::Snakebasket()
	:Add{false}, Replace{false}, Remove{false}
{
}

Snakebasket::~Snakebasket()
{
}

void Snakebasket::AddState(std::unique_ptr<Snakestate> toAdd, bool Replace)
{
	this->Add = true;
	this->NewState = std::move(toAdd);
	this->Replace = Replace;
}

void Snakebasket::PopCurrent()
{
	Remove = true;
}

void Snakebasket::ProcessStateChange()
{
	if (this->Remove && (!this->SnakeStack.empty()))
	{
		this->SnakeStack.pop();
		if (!this->SnakeStack.empty())
		{
			this->SnakeStack.top()->Start();
		}
		Remove = false;
	}
	if (this->Add)
	{
		if (this->Replace && (!this->SnakeStack.empty()))
		{
			this->SnakeStack.pop();
			Replace = false;
		}
		if (!this->Replace && (!this->SnakeStack.empty()))
		{
			this->SnakeStack.pop();
			this->Replace = false;
		}
		if (!this->SnakeStack.empty())
		{
			this->SnakeStack.top()->Pause();
		}
		this->SnakeStack.push(std::move(NewState));
		this->SnakeStack.top()->Init();
		this->SnakeStack.top()->Start();
		this->Add = false;
	}
}

std::unique_ptr<Snakestate>& Snakebasket::GetCurrent()
{
	return this->SnakeStack.top();
}
