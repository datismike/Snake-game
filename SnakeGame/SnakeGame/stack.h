#pragma once

typedef enum Bool
{
	False,
	True
} Bool;

// Data stored in the stack element
typedef struct Data
{
	int x;
	int y;
} Data;

// Stack element
typedef struct Node
{
	Data data;
	struct Node *next;
	struct Node *prev;
} Node;
typedef Node *PNode; // Pointer to stack element

// Move direction
typedef enum Direction
{
	Up,
	Right,
	Down,
	Left
} Direction;

// Stack
typedef struct Stack
{
	// Public
	void (*push)(struct Stack *, Data);
	PNode (*getTopNode)(struct Stack *);
	PNode (*getBottomNode)(struct Stack *);
	Bool (*isEmpty)(struct Stack *);
	void (*move)(struct Stack *);
	void (*setDirection)(struct Stack *, Direction);
	Direction (*getDirection)(struct Stack *);

	// Private
	void *privateData;
} Stack;
Stack *newStack(); // Constructor
void freeStack(Stack *); // Destructor