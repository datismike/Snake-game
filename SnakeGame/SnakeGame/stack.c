#include "stack.h"
#define NULL (((void *)0))

typedef struct PrivateData
{
	PNode topValue;
	PNode bottomValue;
} PrivateData;

static push(Stack *pstack, Data data)
{
	if (pstack->isEmpty(pstack))
	{
		PNode firstNode = (PNode)malloc(sizeof(Node));
		firstNode->data = data;
		firstNode->next = NULL;
		firstNode->prev = NULL;
		((PrivateData *)pstack->privateData)->topValue = firstNode;
		((PrivateData *)pstack->privateData)->bottomValue = firstNode;
		return;
	}
	for (PNode node = ((PrivateData *)pstack->privateData)->bottomValue; node != NULL; node = node->next)
	{
		if (node->next == NULL)
		{
			PNode newTopValue = (PNode)malloc(sizeof(Node));
			newTopValue->data = data;
			newTopValue->next = NULL;
			newTopValue->prev = node;
			node->next = newTopValue;
			((PrivateData *)pstack->privateData)->topValue = newTopValue;
			return;
		}
	}
}

static Data getTopValue(Stack *pstack)
{
	if (((PrivateData *)pstack->privateData)->topValue != NULL)
		return ((PrivateData *)pstack->privateData)->topValue->data;
}

static Data getBottomValue(Stack *pstack)
{
	if (((PrivateData *)pstack->privateData)->topValue != NULL)
		return ((PrivateData *)pstack->privateData)->bottomValue->data;
}

static Bool isEmpty(Stack *pstack)
{
	if ((((PrivateData *)pstack->privateData)->topValue == NULL) && (((PrivateData *)pstack->privateData)->bottomValue == NULL))
		return True;
	else
		return False;
}

Stack *newStack()
{
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->privateData = (PrivateData *)malloc(sizeof(PrivateData));
	((PrivateData *)stack->privateData)->topValue = NULL;
	((PrivateData *)stack->privateData)->bottomValue = NULL;
	stack->push = &push;
	stack->getTopValue = &getTopValue;
	stack->getBottomValue = &getBottomValue;
	return stack;
}

void freeStack(Stack *pstack)
{
	free(pstack);
}