#include "stack.h"
#include "field.h"
#define NULL (((void *)0))

typedef struct PrivateData
{
	PNode topNode;
	PNode bottomNode;
	Direction direction;
} PrivateData;

static void push(Stack *pstack, Data data)
{
	if (pstack->isEmpty(pstack))
	{
		PNode firstNode = (PNode)malloc(sizeof(Node));
		firstNode->data = data;
		firstNode->next = NULL;
		firstNode->prev = NULL;
		((PrivateData *)pstack->privateData)->topNode = firstNode;
		((PrivateData *)pstack->privateData)->bottomNode = firstNode;
		return;
	}
	for (PNode node = ((PrivateData *)pstack->privateData)->bottomNode; node != NULL; node = node->next)
	{
		if (node->next == NULL)
		{
			PNode newTopValue = (PNode)malloc(sizeof(Node));
			newTopValue->data = data;
			newTopValue->next = NULL;
			newTopValue->prev = node;
			node->next = newTopValue;
			((PrivateData *)pstack->privateData)->topNode = newTopValue;
			return;
		}
	}
}

static PNode getTopNode(Stack *pstack)
{
	if (((PrivateData *)pstack->privateData)->topNode != NULL)
		return ((PrivateData *)pstack->privateData)->topNode;
}

static PNode getBottomNode(Stack *pstack)
{
	if (((PrivateData *)pstack->privateData)->topNode != NULL)
		return ((PrivateData *)pstack->privateData)->bottomNode;
}

static Bool isEmpty(Stack *pstack)
{
	if ((((PrivateData *)pstack->privateData)->bottomNode == NULL) && (((PrivateData *)pstack->privateData)->topNode == NULL))
		return True;
	else
		return False;
}

static void move(Stack *pstack)
{
	for (PNode node = ((PrivateData *)pstack->privateData)->bottomNode; node->next != NULL; node = node->next)
	{
		node->data.x = node->next->data.x;
		node->data.y = node->next->data.y;
	}
	switch (((PrivateData *)pstack->privateData)->direction)
	{
		case Up:
		{
			((PrivateData *)pstack->privateData)->topNode->data.y -= CELL_WIDTH;
			break;
		}
		case Right:
		{
			((PrivateData *)pstack->privateData)->topNode->data.x += CELL_WIDTH;
			break;
		}
		case Down:
		{
			((PrivateData *)pstack->privateData)->topNode->data.y += CELL_WIDTH;
			break;
		}
		case Left:
		{
			((PrivateData *)pstack->privateData)->topNode->data.x -= CELL_WIDTH;
			break;
		}
	}
}

static void setDirection(Stack *pstack, Direction direction)
{
	((PrivateData *)pstack->privateData)->direction = direction;
}

static Direction getDirection(Stack *pstack)
{
	return ((PrivateData *)pstack->privateData)->direction;
}

Stack *newStack()
{
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->privateData = (PrivateData *)malloc(sizeof(PrivateData));
	stack->push = &push;
	stack->getTopNode = &getTopNode;
	stack->getBottomNode = &getBottomNode;
	stack->isEmpty = &isEmpty;
	stack->move = &move;
	stack->setDirection = &setDirection;
	stack->getDirection = &getDirection;
	((PrivateData *)stack->privateData)->topNode = NULL;
	((PrivateData *)stack->privateData)->bottomNode = NULL;
	stack->setDirection(stack, Right);

	Data cell;
	cell.x = 0;
	cell.y = 0;
	stack->push(stack, cell);
	
	cell.x = 1 * CELL_WIDTH;
	cell.y = 0;
	stack->push(stack, cell);

	cell.x = 2 * CELL_WIDTH;
	cell.y = 0;
	stack->push(stack, cell);

	cell.x = 3 * CELL_WIDTH;
	cell.y = 0;
	stack->push(stack, cell);

	cell.x = 4 * CELL_WIDTH;
	cell.y = 0;
	stack->push(stack, cell);

	return stack;
}

void freeStack(Stack *pstack)
{
	free(pstack);
}