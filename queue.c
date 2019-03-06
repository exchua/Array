#if 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* list */
typedef struct Node
{
	int data;
	struct Node *pNext;
}NODE,*PNODE;

typedef struct Queue
{
	PNODE front;
	PNODE back;
}QUEUE,*PQUEUE;

bool Init_Queue(PQUEUE pQueue);
bool Push_Queue(PQUEUE pQueue,int data);
bool Pop_Queue(PQUEUE pQueue, int *pData);
bool IsEmpty(PQUEUE pQueue);
void Show_Queue(PQUEUE pQueue);

int main()
{
	QUEUE queue;
	Init_Queue(&queue);

	Push_Queue(&queue, 1);
	Push_Queue(&queue, 2);
	Push_Queue(&queue, 3);
	Push_Queue(&queue, 4);

	Show_Queue(&queue);

	int data;
	for(int i=0;i<5;i++)
	if (Pop_Queue(&queue, &data))
	{
		printf("pop data = %d\n", data);
	}
	else
	{
		printf("pop failed\n");
	}
	Push_Queue(&queue, 4);

	Show_Queue(&queue);

	return 0;
}

bool Init_Queue(PQUEUE pQueue)
{
	pQueue->back = (PNODE)malloc(sizeof(NODE));
	if (NULL == pQueue->back)
	{
		return false;
	}
	else
	{
		pQueue->back->data = -1;
		pQueue->back->pNext = NULL;
		pQueue->front = pQueue->back;
		return true;
	}
}

bool Push_Queue(PQUEUE pQueue, int data)
{
	PNODE pnew = (PNODE)malloc(sizeof(NODE));
	if (NULL == pnew)
	{
		return false;
	}
	else
	{
		pnew->data = data;
		pnew->pNext = pQueue->front;
		pQueue->front = pnew;
		return true;
	}
}

bool Pop_Queue(PQUEUE pQueue, int *pData)
{
	PNODE p,pre;
	if (IsEmpty(pQueue))
	{
		return false;
	}
	else
	{
		pre = p = pQueue->front;
		if (pQueue->front->pNext == pQueue->back)
		{
			*pData = pQueue->front->data;
			pQueue->front = pQueue->back;
			free(p);
			return true;
		}
		while (p->pNext != pQueue->back)
		{
			pre = p;
			p = p->pNext;
		}
		*pData = p->data;
		pre->pNext = pQueue->back;
		free(p);
		return true;
	}
}

bool IsEmpty(PQUEUE pQueue)
{
	if (pQueue->back == pQueue->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void show(PNODE pFront,PNODE pBack)
{
	if (pFront == pBack)
	{
		return;
	}
	else
	{
		show(pFront->pNext, pBack);
		printf("data = %d\n", pFront->data);
	}
}

void Show_Queue(PQUEUE pQueue)
{
	if (IsEmpty(pQueue))
	{
		printf("queue is empty\n");
	}
	else
	{
		/* 偷懒的做法 递归返回的时候显示(倒着显示) */
		show(pQueue->front, pQueue->back);
	}
}
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* array */
typedef struct Array
{
	int *pBase;
	int len;
	int cnt;
}Arr,*pArr;

typedef struct Queue
{
	pArr pArray;
	int front;
	int back;
}QUEUE,*PQUEUE;

bool Init_Queue(PQUEUE pQueue, int len);
bool Push_Queue(PQUEUE pQueue, int data);
bool Pop_Queue(PQUEUE pQueue, int *pData);
bool IsEmpty(PQUEUE pQueue);
bool IsFull(PQUEUE pQueue);
void Show_Queue(PQUEUE pQueue);

int main()
{
	QUEUE queue;
	Init_Queue(&queue,5);
	Push_Queue(&queue, 1);
	Push_Queue(&queue, 2);
	Push_Queue(&queue, 3);
	Push_Queue(&queue, 4);
	Push_Queue(&queue, 5);

	Show_Queue(&queue);

	int data;
	for (int i = 0; i < 2; i++)
	{
		if (Pop_Queue(&queue, &data))
		{
			printf("pop data = %d\n", data);
		}
		else
		{
			printf("pop failed\n");
		}
	}
	Show_Queue(&queue);

	return 0;
}


bool IsEmpty(PQUEUE pQueue)
{
	if (pQueue->back == pQueue->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsFull(PQUEUE pQueue)
{
	if ((pQueue->back + 1) % pQueue->pArray->len == pQueue->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Init_Queue(PQUEUE pQueue, int len)
{
	pQueue->pArray = (pArr)malloc(sizeof(Arr));
	if (NULL == pQueue->pArray)
	{
		return false;
	}
	pQueue->pArray->pBase = (int *)malloc(sizeof(int)*len);
	if (NULL == pQueue->pArray->pBase)
	{
		return false;
	}
	else
	{
		pQueue->pArray->len = len;
		pQueue->pArray->cnt = 0;
		pQueue->front = pQueue->back = pQueue->pArray->cnt;
		return true;
	}
}

bool Push_Queue(PQUEUE pQueue, int data)
{
	if (IsFull(pQueue))
	{
		return false;
	}
	else
	{
		pQueue->pArray->pBase[pQueue->back++] = data;
		pQueue->back %= pQueue->pArray->len;
		return true;
	}
}

bool Pop_Queue(PQUEUE pQueue, int *pData)
{
	if (IsEmpty(pQueue))
	{
		return false;
	}
	else
	{
		*pData = pQueue->pArray->pBase[pQueue->front++];
		pQueue->front %= pQueue->pArray->len;
		pQueue->pArray->cnt = (pQueue->pArray->cnt + 1) % pQueue->pArray->len;
		return true;
	}
}

void Show_Queue(PQUEUE pQueue)
{
	int index;
	if (IsEmpty(pQueue))
	{
		printf("queue is empty\n");
	}
	else
	{
		index = pQueue->front;
		while (index != pQueue->back)
		{
			printf("data = %d\n", pQueue->pArray->pBase[index++]);
			index %= pQueue->pArray->len;
		}
	}
}

