#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)
typedef int type;

typedef struct Node
{
	type data;
	struct Node *pNext;
}Node,*pNode;

pNode Create_List(void);
void Show_List(pNode pHead);
int Length_List(pNode pHead);
bool Insert_List(pNode pHead,int const pos,int const data);
bool Delet_List(pNode pHead, int const pos, int *pdata);
void Sort_List(pNode pHead, int const moder);

int StrLen(char const *pStr)
{
	int iLen = 0;
	while (*pStr++)
	{
		++iLen;
	}
	return iLen;
}

char *InversionString(unsigned char *pucStr)
{
	unsigned char ucTmp;
	int iLen = StrLen(pucStr);
	if (iLen < 1)
	{
		return NULL;
	}
	for (unsigned char *pBegin = pucStr, *pEnd = pucStr + iLen - 1; pBegin < pEnd; ++pBegin, --pEnd)
	{
		ucTmp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = ucTmp;
	}
	return pucStr;
}

bool IsNum(unsigned char ch)
{
	if (ch <= '9'&&ch >= '0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsAllNum(unsigned char const *pucNum)
{
	while (*pucNum)
	{
		if (!IsNum(*pucNum++))
		{
			return false;
		}
	}
	return true;
}

int Atoi(char *pStr)
{
	int ret = 0;
	while (*pStr)
	{
		ret *= 10;
		ret += *pStr++ - 48;
	}
	return ret;
}

int main()
{	
	pNode pHead = NULL;
	
	pHead = Create_List();

	int data;
	int ch;
	int n;
	getchar();
	while (1)
	{		
		printf("	 --------------Menu--------------\n");
		printf("	|s	: Show_List		|\n");
		printf("	|i	: Insert_List		|\n");
		printf("	|d	: Delet_List		|\n");
		printf(" 	---------------------------------\n");
		
		ch = getchar();
		getchar();
		printf("get char is %c\n", ch);
		//system("cls");
		switch (ch)
		{
		case 's':
		case 'S':
		{
			Show_List(pHead);
		}break;

		case 'i':
		case 'I':
		{
			printf("插入位置:");
			scanf("%d", &n);
			printf("插入数据:");
			scanf("%d", &data);
			if (!Insert_List(pHead, n, data))
			{
				printf("插入失败\n");
			}
			getchar();
		}break;

		case 'd':
		case 'D':
		{
			printf("删除第几个元素:");
			scanf("%d", &n);
			if (!Delet_List(pHead, n, &data))
			{
				printf("删除失败\n");
			}
			printf("\ndel data = %d\n", data);
			getchar();
		}break;
		}
		
	}
	return 0;
} 

pNode Create_List(void)
{
	bool bFlag = false;
	int iNum = 0;
	int iTmp = 0;
	unsigned char ucNum[10] = { 0 };
	//sizeof(int) is 4
	//INT_MAX = 2147483647
	do {
		if (bFlag)
		{
			printf("输入错误，请重新输入数字:");
		}
		else
		{
			printf("请输入数字:");
		}
		scanf_s("%s", &ucNum, 10);
		bFlag = true;
	} while (!IsAllNum(ucNum));

	iNum = Atoi(ucNum);
	pNode pHead = (pNode)malloc(sizeof(Node));
	pHead->data = 0;
	pHead->pNext = NULL;
	if (NULL == pHead)
	{
		printf("分配失败\n");
		exit(-1);
	}
	pNode pTail = pHead;
	pNode pTmp;
	for (int i = 0; i < iNum; i++)
	{
		printf("请输入:");
		scanf_s("%d", &iTmp);
		pTmp = (pNode)malloc(sizeof(Node));
		pTmp->pNext = NULL;
		pTmp->data = iTmp;
		pTail->pNext = pTmp;
		pTail = pTail->pNext;
	}
	return pHead;
}

bool IsEmpty_List(pNode pHead)
{
	if (pHead->pNext == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Show_List(pNode pHead)
{
	pNode pHeader = pHead->pNext;
	if (IsEmpty_List(pHead))
	{
		printf("the list is empty\n");
	}
	while (pHeader)
	{
		printf("data = %d \n", pHeader->data);
		pHeader = pHeader->pNext;
	}
}

int Length_List(pNode pHead)
{
	int iLen = 0;
	pNode pHeader = pHead->pNext;
	while (pHeader)
	{
		++iLen;
		pHeader = pHeader->pNext;
	}
	return iLen;
}

static swap(int *const pi, int *const pj)
{
	int tmp;
	tmp = *pi;
	*pi = *pj;
	*pj = tmp;
}

void Sort_List(pNode pHead, int const moder)
{

	switch (moder)
	{
	case 1:
	{		/* 冒泡 */
		for (pNode pi = pHead; NULL != pi; pi = pi->pNext)
		{
			for (pNode pj = pi; NULL != pj->pNext; pj = pj->pNext)
			{
				if (pj->data > pj->pNext->data)
				{
					swap(&pj->data, &pj->pNext->data);
				}
			}
		}
		break;
	}
	case 2:
	{	/* 选择 */
		for (pNode pi = pHead; NULL != pi; pi = pi->pNext)
		{
			for (pNode pj = pi->pNext; NULL != pj; pj = pj->pNext)
			{
				if (pj->data < pi->data)	// 小->大
				{
					swap(&pj->data, &pi->data);
				}
			}
		}
		break;
	}
	}
}

bool Insert_List(pNode pHead, int const pos, int const data)
{
	int iLen = 0;
	pNode pHeader = pHead;
	pNode pnew;
	while (NULL != pHeader && iLen < pos - 1)
	{
		pHeader = pHeader->pNext;
		iLen++;
	}
	if (iLen > pos - 1 || NULL == pHeader)
	{
		return false;
	}
	pnew = (pNode)malloc(sizeof(Node));
	if (NULL == pnew)
	{
		printf("内存分配失败\n");
		exit(-1);
	}
	pnew->data = data;
	pnew->pNext = pHeader->pNext;
	pHeader->pNext = pnew;
	return true;
}

bool Delet_List(pNode pHead, int const pos, int *pdata)
{
	int iLen = 0;
	pNode pHeader = pHead;
	pNode pdel;
	while (NULL != pHeader->pNext && iLen < pos - 1)
	{
		pHeader = pHeader->pNext;
		iLen++;
	}
	if (iLen > pos - 1 || NULL == pHeader)
	{
		return false;
	}
	pdel = pHeader->pNext;
	*pdata = pdel->data;
	pHeader->pNext = pHeader->pNext->pNext;
	free(pdel);
	return true;
}
