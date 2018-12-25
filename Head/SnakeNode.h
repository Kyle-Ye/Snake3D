#pragma once
class SnakeNode:
	public Ball
{
	friend class Snake;
public:
	SnakeNode();
	~SnakeNode();
private:
	SnakeNode* next;
	SnakeNode* before;
};

