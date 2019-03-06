#if 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int type;

/* list */
typedef struct Node
{
	type data;
	struct Node *pNext;
}NODE,*PNODE;

typedef struct Stack
{
	PNODE pTop;
	PNODE pButton;
}STACK,*PSTACK;


bool Init_Stack(PSTACK pStack);
bool Push_Stack(PSTACK pStack, int data);
bool IsEmpty(PSTACK pStack);
bool Pop_Stack(PSTACK pStack, int *pData);
void Show_Stack(PSTACK pStack);

int main()
{
	STACK stack;
	Init_Stack(&stack);
	Push_Stack(&stack, 1);
	Push_Stack(&stack, 2);
	Push_Stack(&stack, 3);
	Push_Stack(&stack, 4);
	Push_Stack(&stack, 5);

	Show_Stack(&stack);
	
	int data;
	for (int i = 0; i < 5; i++)
	{
		if (Pop_Stack(&stack, &data))
		{
			printf("pop data = %d\n", data);
		}
		else
		{
			printf("pop failed\n");
		}
	}
	Show_Stack(&stack);
	
	return 0;
}

bool Init_Stack(PSTACK pStack)
{
	pStack->pTop = (PNODE)malloc(sizeof(NODE));
	if (NULL == pStack)
	{
		return false;
	}
	else
	{
		pStack->pButton = pStack->pTop;
		pStack->pTop->pNext = NULL;
		pStack->pTop->data = -1;
		return true;
	}
}

bool Push_Stack(PSTACK pStack, int data)
{
	PNODE pnew = (PNODE)malloc(sizeof(NODE));
	if (NULL == pnew)
	{
		return false;
	}
	else
	{
		pnew->data = data;
		pnew->pNext = pStack->pTop;
		pStack->pTop = pnew;
		return true;
	}
}

bool IsEmpty(PSTACK pStack)
{
	if (pStack->pButton == pStack->pTop)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Pop_Stack(PSTACK pStack, int *pData)
{
	PNODE p = pStack->pTop;
	if (IsEmpty(pStack))
	{
		return false;
	}
	else
	{
		pStack->pTop = p->pNext;
		*pData = p->data;
		free(p);
		return true;
	}
}

void Show_Stack(PSTACK pStack)
{
	PNODE p = pStack->pTop;
	while (p != pStack->pButton)
	{
		printf("data = %d\n", p->data);
		p = p->pNext;
	}
}
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* array */
typedef struct Stack
{
	int *pBase;
	int len;
	int cnt;
}STACK,*PSTACK;

bool Init_Stack(PSTACK pStack,int len);
bool Push_Stack(PSTACK pStack, int data);
bool Pop_Stack(PSTACK pStack, int *pData);
bool IsEmpty(PSTACK pStack);
bool IsFull(PSTACK pStack);
void Show_Stack(PSTACK pStack);


int main()
{
	STACK stack;
	Init_Stack(&stack,5);
	Push_Stack(&stack, 1);
	Push_Stack(&stack, 2);
	Push_Stack(&stack, 3);
	Push_Stack(&stack, 4);
	Push_Stack(&stack, 5);
	
	printf("ret = %d\n", Push_Stack(&stack, 5));
	
	Show_Stack(&stack);
	int data;
	for (int i = 0; i < 6; i++)
	{
		if (Pop_Stack(&stack, &data))
		{
			printf("pop data = %d\n", data);
		}
		else
		{
			printf("pop failed\n");
		}
	}

	Show_Stack(&stack);

	return 0;
}


bool Init_Stack(PSTACK pStack,int len)
{
	pStack->pBase = (int *)malloc(sizeof(int)*len);
	if (NULL == pStack->pBase)
	{
		return false;
	}
	else
	{
		pStack->cnt = -1;
		pStack->len = len;
		return true;
	}
}

bool Push_Stack(PSTACK pStack, int data)
{
	if (IsFull(pStack))
	{
		return false;
	}
	else
	{
		pStack->pBase[++pStack->cnt] = data;
		return true;
	}
}

bool Pop_Stack(PSTACK pStack, int *pData)
{
	if (IsEmpty(pStack))
	{
		return false;
	}
	else
	{
		*pData = pStack->pBase[pStack->cnt--];
		return true;
	}
}

bool IsEmpty(PSTACK pStack)
{
	if (-1 == pStack->cnt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsFull(PSTACK pStack)
{
	if (pStack->len - 1 == pStack->cnt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Show_Stack(PSTACK pStack)
{
	int index;
	if (IsEmpty(pStack))
	{
		printf("stack is empty\n");
	}
	else
	{
		index = pStack->cnt;
		while (index >= 0)
		{
			printf("data = %d \n", pStack->pBase[index--]);
		}
	}
}