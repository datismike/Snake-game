#pragma once

typedef enum Bool
{
	True,
	False
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

// Stack
typedef struct Stack
{
	// Public
	void (*push)(struct Stack *, Data);
	Data (*getTopValue)(struct Stack *);
	Data (*getBottomValue)(struct Stack *);
	Bool (*isEmpty)(struct Stack *);

	// Private
	void *privateData;
} Stack;
Stack *newStack(); // Constructor
void freeStack(Stack *); // Destructor