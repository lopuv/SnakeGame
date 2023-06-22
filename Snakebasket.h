#pragma once
#include "Snakestate.h"
#include <stack>
#include <memory>

class Snakebasket
{
private:
	std::stack<std::unique_ptr<Snakestate>> SnakeStack;
	std::unique_ptr<Snakestate> NewState;

	bool Add;
	bool Replace;
	bool Remove;

public:
	Snakebasket();
	~Snakebasket();

	void AddState(std::unique_ptr<Snakestate> toAdd, bool Replace = false);
	void PopCurrent();
	void ProcessStateChange();
	std::unique_ptr<Snakestate>& GetCurrent();
};

